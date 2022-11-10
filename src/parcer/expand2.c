/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 13:29:52 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 11:55:27 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include "../hdr/ms_enums.h"
#include "../utils/hdr/token_utils.h"
#include <stdlib.h>

static void	swap_head(t_token **head, t_token **expand)
{
	t_token	*temp_head;
	t_token	*temp_exp;

	if ((*expand)->token_value == NULL)
	{
		temp_exp = *expand;
		*expand = (*expand)->next;
		free(temp_exp);
		temp_head = (*head);
		*head = (*head)->next;
		if (temp_head->token_value)
			free(temp_head->token_value);
		free(temp_head);
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

t_token	*expand_to_null(t_token *current)
{
	t_token	*nulltoken;

	nulltoken = malloc(sizeof(t_token));
	if (!nulltoken)
		exit(EXIT_FAILURE);
	nulltoken->i = current->i;
	nulltoken->token_label = current->token_label;
	nulltoken->start_pos = current->start_pos;
	nulltoken->end_pos = current->end_pos;
	nulltoken->token_value = NULL;
	nulltoken->next = NULL;
	return (nulltoken);
}
