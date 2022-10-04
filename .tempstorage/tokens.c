/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 14:12:48 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/14 15:57:16 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h> //path max
#include <unistd.h> //getcwd 

#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <string.h>
#include <stdbool.h>
#include "../../libft/libft.h"
#include "hdr/lexer.h"

#define KNRM  "\e[0m"
#define KRED  "\e[1;31m"

t_token	*new_node(int index, int label, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->i = index;
	new->token_label = label;
	new->token_value = value;
	new->next = NULL;
	return (new);
}

t_token	*tokenlst_last(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

char	*allocate_token_value(char *ret, int count, int i)
{
	char	*token;

	if (count == 0)
		return (NULL);
	token = malloc(sizeof(char) * count + 1);
	ft_strlcpy(token, &ret[i], count + 1);
	return (token);
}

void	add_token_to_list(t_token **head, char *token_value, int *token_label)
{
	static int	count = 0;
	t_token		*node;

	if (!token_value || !head)
		return ;
	count = count + 1;
	node = new_node(count, *token_label, token_value);
	*token_label = NO_LABEL;
	if (!*head)
		*head = node;
	else
		tokenlst_last(*head)->next = node;
}

int	add_token_label(char current, char next_char)
{
	int	token_label;

	token_label = 0;
	if (current == '>' && next_char == '>')
		token_label = GREATGREAT;
	else if (current == '<' && next_char == '<')
		token_label = LESSLESS;
	else if (current == '<' && next_char != '<')
		token_label = LESS;
	else if (current == '>' && next_char != '>')
		token_label = GREAT;
	else if (current == '|')
		token_label = PIPE;
	return (token_label);
}