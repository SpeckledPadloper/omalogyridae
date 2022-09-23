/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:18:33 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/23 18:46:03 by mteerlin      ########   odam.nl         */
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

int	main(int argc, char **argv, char **env)
{
	t_token		*head;
	char		*input;
	t_base_args	*b_args;
	char		*prompt;

	b_args = set_base_args(argc, argv, env);
	input = "";
	prompt = ft_strjoin(SHLNAME, "> ");
	while (input != NULL)
	{
		input = readline(prompt);
		head = lex(input);
		if (head == NULL)
			continue ;
		add_history(input);
		free(input);
		parce(head, &b_args->env);
	}
	free(prompt);
	free(b_args);
	return (0);
}
