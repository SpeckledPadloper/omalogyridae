/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:18:33 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/28 14:03:42 by mteerlin      ########   odam.nl         */
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
	t_base_args	*b_args;
	t_metadata	data;
	t_fd_list	fd_list;
	t_exec_list_sim *ret;
	char		*prompt;
	int			status;
	struct termios	term;

	status = 0;
	// atexit(&leaksatexit);
	sig_setup(PROC_PARNT);
	if (WTERMSIG(status) == SIGINT)
		data.exitstatus = 1;
	init_metadata(&data, &fd_list, env);
	b_args = set_base_args(argc, argv, env);
	input = "";
	prompt = ft_strjoin(SHLNAME, "> ");
	if (!prompt)
		exit(EXIT_FAILURE);
	while (input != NULL)
	{
		input = readline(prompt);
		if (input == NULL)
			input = input_eof();
		add_history(input);
		head = lex(input, &data);
		if (head == NULL)
			continue ;
		free(input);
		reset_metadata(&data, &fd_list, env);
		ret = parce(head, &b_args->env);
		//test_simple_command(ret);
		executer(&data, ret);
		printf("exitstatus: [%d]\n", data.exitstatus);
		// system("leaks minishell");
		// exit(data.exitstatus);
		simple_cmd_clear(&ret);
	}
	free(prompt);
	free(b_args);
	return (data.exitstatus);
}
