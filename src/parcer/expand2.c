/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 13:29:52 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 16:03:23 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include "../utils/hdr/token_utils.h"
#include "../../libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>

static void	swap_head(t_token **head, t_token **expand)
{
	t_token	*temp_head;
	t_token	*temp_exp;

	if ((*expand)->token_value == NULL)
	{
		(*head) = (*head)->next;
	}
	else
	{
		temp_head = (*head)->next;
		temp_exp = (*expand)->next;
		if ((*head)->token_value)
			free((*head)->token_value);
		free(*head);
		(*head) = (*expand);
		(*head)->next = temp_head;
		(*expand) = temp_exp;
	}
}

static void	swap_lst(t_token **itterhead, t_token **itterexp)
{
	t_token	*temp_head;
	t_token	*temp_exp;

	temp_head = (*itterhead)->next->next;
	if ((*itterhead)->next->token_value)
		free((*itterhead)->next->token_value);
	free((*itterhead)->next);
	(*itterhead)->next = *itterexp;
	if (!itterexp)
		return ;
	temp_exp = (*itterexp)->next;
	(*itterhead)->next->next = temp_head;
	*itterexp = temp_exp;
}

void	link_expand_tokens(t_token **head, t_token **expand)
{
	t_token	*itterhead;
	t_token	*itterexp;

	if (!head || !expand || !(*expand))
		return ;
	if ((*head) && (*head)->token_label == EXPAND)
		swap_head(head, expand);
	itterhead = *head;
	itterexp = *expand;
	while (itterhead && itterhead->next)
	{
		if (itterhead->next->token_label == EXPAND)
			swap_lst(&itterhead, &itterexp);
		if (itterhead)
			itterhead = itterhead->next;
	}
}

t_token	*expand_to_null(void)
{
	t_token	*nulltoken;

	nulltoken = ft_calloc(1, sizeof(t_token));
	if (!nulltoken)
		exit(EXIT_FAILURE);
	return (nulltoken);
}
