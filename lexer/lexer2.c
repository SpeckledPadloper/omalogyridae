/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:49:01 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/08/24 17:26:14 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"
#include "lexer.h"

typedef struct s_base_args
{
	int		argc;
	char	**argv;
	char	**env;
}	t_base_args;

typedef struct s_open_qe
{
	bool	open_squote;
	bool	open_dquote;
	bool	expand;
}	t_open_qe;

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
	t_token		*head;
	t_token		*node;
	int			i;
	int			cnt;
	int			token_label;
	char		*token_value;
	t_open_qe	open_qe;

	i = 0;
	cnt = 0;
	head = NULL;
	node = new_node(0, NO_LABEL, NULL);
	while (input[i])
	{
		if (is_token_separator(input[i]))
		{
			token_value = allocate_token_value(input, cnt, (i - cnt));
			add_token_to_list(&head, token_value, &token_label);
			token_value = do_special_char(input, &i, &token_label);
			add_token_to_list(&head, token_value, &token_label);
			cnt = -1;
		}
		if (is_literal(ret[i]))
		{
			if (!is_token_separator(input[i - 1]))
			{
				token_value = allocate_token_value(input, cnt, (i - cnt));
				add_token_to_list(&head, token_value, &token_label);
				cnt = -1;
			}
			else
				do_quotes(ret, &i, &count, &token_label);
		}
		i++;
		cnt++;
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_base_args	*b_args;
	char		ctrl_d;

	b_args = set_base_args(argc, argv, env);
	input = " ";
	ctrl_d = '\0';
	while (input != NULL)
	{
		input = readline("SpeckledPadloper> ");
		lex(input);
		add_history(input);
		free(input);
	}
}
