/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:18:33 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/05 15:58:42 by lwiedijk      ########   odam.nl         */
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
#include "executer/executer.h"

int	main(int argc, char **argv, char **env)
{
	t_token		*head;
	char		*input;
	t_base_args	*b_args;
	t_metadata	data;
	t_fd_list	fd_list;
	char		*prompt;

	init_metadata(&data, &fd_list, env);
	b_args = set_base_args(argc, argv, env);
	input = "";
	prompt = ft_strjoin(SHLNAME, "> ");
	while (input != NULL)
	{
		input = readline(prompt);
		add_history(input);
		head = lex(input);
		if (head == NULL)
			continue ;
		free(input);
		parce(head, &b_args->env);
		executer(&data, head);
	}
	free(prompt);
	free(b_args);
	return (data.exitstatus);
}
