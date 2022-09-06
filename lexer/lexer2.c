/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:49:01 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/06 19:28:53 by mteerlin      ########   odam.nl         */
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

bool	is_token_separator(char current)
{
	if (current == ' ' || current == '<' || current == '>' || \
		current == '|' || current == '"' || current == '\'' || current == '$')
		return (true);
	return (false);
}

bool	is_whitespace(char current)
{
	if (current == ' ' || (current >= 9 && current <= 13))
		return (true);
	return (false);
}

void	lex(char *input)
{
	t_token		*head;
	t_token		*node;
	int			i;
	int			cnt;
	int			token_label;

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


