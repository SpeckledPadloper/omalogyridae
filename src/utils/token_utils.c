/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 12:29:38 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/22 19:44:05 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "../lexer/hdr/lexer.h"
#include "hdr/token_utils.h"
#include "../../libft/libft.h"
#include "../hdr/structs.h"
#include "../lexer/hdr/errors.h"
#include "../lexer/hdr/charchecks.h"

t_token	*new_node(int index, char *value, int state, t_line_nav *lnav)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->i = index;
	if (state == STATE_SQUOTE)
		new->token_label = SINGLE_QUOTE;
	else if (state == STATE_DQUOTE)
		new->token_label = DOUBLE_QUOTE;
	else
		new->token_label = add_token_label(value[0], value[1]);
	new->token_value = value;
	if (new->token_label <= PIPE)
	{
		new->start_pos = (lnav->i + 1) - lnav->count;
		new->end_pos = lnav->i;
	}
	else
	{
		new->start_pos = lnav->i - lnav->count;
		new->end_pos = lnav->i - 1;
	}
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

char	*allocate_token_value(t_line_nav *lnav)
{
	char	*token;
	int		start;

	start = lnav->i - lnav->count;
	if (start < 0)
		return (NULL);
	token = malloc(sizeof(char) * (lnav->count + 1));
	ft_strlcpy(token, &lnav->ret[start], (lnav->count + 1));
	return (token);
}

bool	add_token_to_list(t_token **head, char *val, int s, t_line_nav *lnav)
{
	static int	token_index = 0;
	t_token		*node;

	if (!val || !head)
		return (true);
	if (*head == NULL && !ft_strncmp(val, "|", 2))
	{
		syntax_error(val);
		return (false);
	}
	token_index = token_index + 1;
	node = new_node(token_index, val, s, lnav);
	if (*head && ((tokenlst_last(*head)->token_label < PIPE \
		&& node->token_label <= PIPE) \
		|| (tokenlst_last(*head)->token_label == PIPE \
		&& node->token_label == PIPE)))
	{
		syntax_error(val);
		return (false);
	}
	if (!*head)
		*head = node;
	else
		tokenlst_last(*head)->next = node;
	return (true);
}

int	add_token_label(char current, char next_char)
{
	int	token_label;

	token_label = 0;
	if (current == '<' && next_char != '<')
		token_label = LESS;
	else if (current == '<' && next_char == '<')
		token_label = LESSLESS;
	else if (current == '>' && next_char != '>')
		token_label = GREAT;
	else if (current == '>' && next_char == '>')
		token_label = GREATGREAT;
	else if (current == '|')
		token_label = PIPE;
	else if (current == '\'')
		token_label = SINGLE_QUOTE;
	else if (current == '"')
		token_label = DOUBLE_QUOTE;
	else if (current == '$')
		token_label = EXPAND;
	else
		token_label = NO_LABEL;
	return (token_label);
}

// void	stitch_token(t_token **token, char *stitch_value, int *stitch_label)
// {
// 	t_token	*node;

// 	if (!stitch_value || !token)
// 		return ;
// 	node = new_node(0, stitch_value);
// 	*stitch_label = NO_LABEL;
// 	if (!*token)
// 		*token = node;
// 	else
// 		tokenlst_last(*token)->next = node;
// }