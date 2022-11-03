/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:18:33 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/27 14:13:29 by lwiedijk      ########   odam.nl         */
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

static char	*input_eof(void)
{
	char	*ret;

	ret = ft_strdup("exit");
	if (ret == NULL)
		exit(EXIT_FAILURE);
	return (ret);
}

//static void	signal_handler(int sig)
//{
//	char	*prompt;
//
//	if (sig == SIGINT)
//		return ;
//	else if (sig == SIGQUIT)
//		return ;
//}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("\b\b  ", STDOUT_FILENO);
		write(1, "speckeldStuff: ", 15);
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
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

	// atexit(&leaksatexit);
	init_metadata(&data, &fd_list, env);
	input = "";
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	kill(data.lastpid, SIGQUIT);
	// kill(data.lastpid, SIGINT);
	while (input != NULL)
	{
		input = readline(SHLPROM);
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
		// printf("exitstatus: [%d]\n", data.exitstatus);
		//system("leaks minishell");
		// exit(data.exitstatus);
		simple_cmd_clear(&ret);
	}
	return (data.exitstatus);
}
