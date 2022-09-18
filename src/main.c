/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:18:33 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/18 20:17:24 by mteerlin      ########   odam.nl         */
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

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_base_args	*b_args;
	char		*prompt;
	char		ctrl_d;

	b_args = set_base_args(argc, argv, env);
	input = "";
	ctrl_d = '\0';
	prompt = ft_strjoin(SHLNAME, "> ");
	while (input != NULL)
	{
		input = readline(prompt);
		lex(input);
		add_history(input);
		free(input);
	}
	free(prompt);
	free(b_args);
	return (0);
}
