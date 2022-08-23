/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:49:01 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/08/23 15:44:24 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

typedef struct s_base_args
{
	int		argc;
	char	**argv;
	char	**env;
}	t_base_args;

t_base_args	*set_base_args(int argc, char **argv, char **env)
{
	t_base_args	*b_args;

	b_args = malloc(sizeof(t_base_args));
	b_args->argc = argc;
	b_args->argv = argv;
	b_args->env = env;
	return (b_args);
}

void	lex(char *input)
{
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_base_args	*b_args;

	b_args = set_base_args(argc, argv, env);
	input = " ";
	while (input != NULL)
	{
		input = readline("SpeckledPadloper>");
		lex(input);
		add_history(input);
		free(input);
	}
}
