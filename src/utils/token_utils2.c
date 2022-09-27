/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:19:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/27 20:25:54 by mteerlin      ########   odam.nl         */
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

void	tokenlst_cut_one(t_token *head, t_token **target)
{
	t_token	*temp;

	if (!head || !target)
		return ;
	if (head == *target)
	{
		temp = (*target);
		(*target) = (*target)->next;
		temp->next = NULL;
		tokenlst_clear(&temp);
		return ;
	}
	temp = head;
	while (temp->next != NULL && temp->next != *target)
		temp = temp->next;
	temp->next = NULL;
	temp = *target;
	*target = (*target)->next;
	temp->next = NULL;
	tokenlst_clear(&temp);
}

void	cut_token(t_token **head, t_token **tail)
{
	*head = (*tail)->next->next;
	free((*tail)->next->token_value);
	free((*tail)->next);
	(*tail)->next = NULL;
}
