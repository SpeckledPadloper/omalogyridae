/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_section_utils2.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 15:05:14 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/01 19:54:35 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/hdr/lexer.h"
#include <stdlib.h>
#include "../hdr/structs.h"
#include "../error/error.h"
#include "hdr/token_utils.h"
#include "../parcer/hdr/separate.h"

#include <stdio.h>
#include <unistd.h>

t_token_section	*rdirlst_split(t_token **head, int f1, int f2)
{
	t_token_section	*first;
	t_token			*temp;
	int				state;

	if (!head || !(*head))
		return (NULL);
	first = NULL;
	if ((*head)->token_label == LESSLESS)
		(*head)->next->start_pos = -1;
	if ((*head)->token_label == GREATGREAT)
		(*head)->next->start_pos = -2;
	temp = (*head)->next;
	(*head)->next = NULL;
	tokenlst_clear(head);
	*head = temp;
	while (temp && temp->next)
	{
		if (temp->next->token_label == f1 || temp->next->token_label == f2)
		{
			state = temp->next->token_label;
			add_section_to_list(&first, *head);
			cut_token(head, &temp);
			temp = *head;
			if (state == LESSLESS)
				(*head)->start_pos = -1;
			if (state == GREATGREAT)
				(*head)->start_pos = -2;
		}
		else if (temp)
			temp = temp->next;
	}
	add_section_to_list(&first, *head);
	return (first);
}

t_token_section	*tokenlst_split(t_token **head)
{
	t_token_section	*first;
	t_token			*temp;

	if (!head || !(*head))
		return (NULL);
	first = NULL;
	temp = *head;
	while (temp && temp->next)
	{
		if (temp->next->token_label == PIPE)
		{
			add_section_to_list(&first, *head);
			cut_token(head, &temp);
			temp = *head;
		}
		else if (temp)
			temp = temp->next;
	}
	add_section_to_list(&first, *head);
	return (first);
}

void	clear_section(t_token_section	**head)
{
	t_token_section	*temp;

	if (!head || !(*head))
		return ;
	temp = *head;
	while (temp)
	{
		*head = (*head)->next;
		tokenlst_clear(&temp->head);
		free(temp);
		temp = (*head);
	}
}
