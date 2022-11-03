/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:18:33 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/03 13:54:10 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h> //path max
#include <unistd.h> //getcwd 

#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <string.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "lexer/hdr/lexer.h"
#include "hdr/structs.h"
#include "parcer/hdr/parcer.h"
#include "executer/hdr/executer.h"
#include "utils/hdr/simple_cmd_utils.h"
#include "tests/tests.h"

#include <sys/wait.h>
#include <signal.h>
#include <term.h>
#include <termios.h>
#include "signals/hdr/sigpadloper.h"

static char	*input_eof(void)
{
	char	*ret;

	ret = ft_strdup("exit");
	if (ret == NULL)
		exit(EXIT_FAILURE);
	return (ret);
}

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
		return ;
	else if (sig == SIGQUIT)
		return ;
}

static void	leaksatexit(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_token		*head;
	char		*input;
	t_metadata	data;
	t_fd_list	fd_list;
	t_exec_list_sim *ret;
	char		*prompt;
	int			status;
	struct termios	term;

	status = 0;
	sig_setup(PROC_PARNT);
	init_metadata(&data, &fd_list, env);
	printf("exitstatus: [%d]\n", data.exitstatus);
	input = "";
	prompt = ft_strjoin(SHLNAME, "> ");
	if (!prompt)
		exit(EXIT_FAILURE);
	while (input != NULL)
	{
		if (WTERMSIG(status) == SIGINT)
			data.exitstatus = 1;
		input = readline(prompt);
		if (input == NULL)
			input = input_eof();
		if (input[0] != '\n')
			add_history(input);
		head = lex(input, &data);
		free(input);
		if (head == NULL)
			continue ;
		ret = parce(head, &data.padloper_envp, &data);
		reset_metadata(&data, &fd_list, env);
		if ((ret->cmd && !ret->cmd[0]) && !ret->infile_list && !ret->outfile_list)
		{
			simple_cmd_clear(&ret);
			continue ;
		}
		// test_simple_command(ret);
		executer(&data, ret);
		// printf("exitstatus: [%d]\n", data.exitstatus);
		// system("leaks minishell");
		simple_cmd_clear(&ret);
	}
	free(prompt);
	return (data.exitstatus);
}
