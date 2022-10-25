/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:18:33 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/25 14:19:04 by mteerlin      ########   odam.nl         */
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

int	main(int argc, char **argv, char **env)
{
	t_token		*head;
	char		*input;
	t_base_args	*b_args;
	t_metadata	data;
	t_fd_list	fd_list;
	t_exec_list_sim *ret;
	char		*prompt;

	init_metadata(&data, &fd_list, env);
	b_args = set_base_args(argc, argv, env);
	input = "";
	prompt = ft_strjoin(SHLNAME, "> ");
	while (input != NULL)
	{
		input = readline(prompt);
		add_history(input);
		head = lex(input, &data);
		if (head == NULL)
			continue ;
		free(input);
		reset_metadata(&data, &fd_list, env);
		ret = parce(head, &b_args->env);
		test_simple_command(ret);
		executer(&data, ret);
		simple_cmd_clear(&ret);
	}
	free(prompt);
	free(b_args);
	return (data.exitstatus);
}
