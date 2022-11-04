/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 14:05:26 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/04 15:02:41 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include "hdr/sigpadloper.h"
#include <signal.h>
#include "../../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "../hdr/structs.h"
#include <termios.h>
#include <stdlib.h>

/*

set_signal(1)

set_signal(3);

if == 1
	signal(sigint, main_minishell)
if == 2
	exit (123) // heredoc break
if == 3
	signal(sigint, SIGDFL);

*/

static void	empty_sighandle(int sig)
{
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exitstatus = 1;
}

static void	heredoc_sighandle(int sig)
{
	exit(1);
}

static void	quit_handle(int sig)
{
	exit(128 + sig);
}

int	sig_exit(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(SIGQUIT, 2);
		ft_putchar_fd('\n', 2);
	}
	return (128 + WTERMSIG(status));
}

void	change_tcattr(int state)
{
	struct termios	term;

	tcgetattr(2, &term);
	if (state == PROC_PARNT)
		term.c_lflag &= ~ECHOCTL;
	if (state == PROC_CHLD)
	{
		term.c_lflag |= ISIG;
		term.c_lflag |= ECHOCTL;
	}
	tcsetattr(2, TCSANOW, &term);
}

void	sig_setup(int state)
{
	struct termios	term;

	change_tcattr(state);
	if (state == PROC_PARNT)
	{
		signal(SIGINT, &empty_sighandle);
		signal(SIGQUIT, SIG_IGN);
	}
	if (state == PROC_CHLD)
	{
		signal(SIGQUIT, &quit_handle);
		signal(SIGINT, SIG_DFL);
	}
	if (state == PROC_HEREDOC)
	{
		signal(SIGINT, &heredoc_sighandle);
	}
}
