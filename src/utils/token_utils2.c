/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:19:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/26 19:54:53 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/hdr/lexer.h"
#include <stdlib.h>
#include "../hdr/structs.h"
#include "../error/error.h"

#include <stdio.h>
#include <unistd.h>

void	tokenlst_clear(t_token **head)
{
	t_token	*temp;

	if (head == NULL || *head == NULL)
		return ;
	while (*head)
	{
		temp = (*head)->next;
		if (((*head)->token_value))
			free((*head)->token_value);
		free(*head);
		*head = temp;
	}
	*head = NULL;
}

void	tokenlst_cut_one(t_token **head, t_token **target)
{
	t_token	*temp;

	if (!head || !target)
		return ;
	temp = *head;
	while (temp->next != NULL && temp->next != *target)
		temp = temp->next;
	temp->next = NULL;
	temp = *target;
	*target = (*target)->next;
	temp->next = NULL;
	tokenlst_clear(&temp);
}

t_token_section	*new_token_section(t_token *head)
{
	t_token_section	*new;

	new = malloc(sizeof(t_token_section));
	if (!new)
		mem_all_error();
	new->head = head;
	new->next = NULL;
	return (new);
}

t_token_section	*token_section_last(t_token_section *first)
{
	t_token_section	*ret;

	ret = first;
	while (ret->next != NULL)
		ret = ret->next;
	return (ret);
}

void	cut_token(t_token **head, t_token **tail)
{
	*head = (*tail)->next->next;
	free((*tail)->next->token_value);
	free((*tail)->next);
	(*tail)->next = NULL;
}
