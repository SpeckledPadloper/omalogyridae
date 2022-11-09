/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_section_utils2.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 15:05:14 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 21:03:49 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../hdr/structs.h"
#include "../hdr/ms_enums.h"
#include "hdr/token_utils.h"
#include "../parcer/hdr/separate.h"

static void	rdirlst_split_setstart(int state, int *start_pos)
{
	if (state == LESSLESS)
		*start_pos = -1;
	if (state == GREATGREAT)
		*start_pos = -2;
}

static void	rdirlst_cut(t_token **head, t_token **temp, t_token_section **first)
{
	int	state;

	state = (*temp)->next->token_label;
	add_section_to_list(first, *head);
	cut_token(head, temp);
	*temp = *head;
	rdirlst_split_setstart(state, &(*head)->start_pos);
}

t_token_section	*rdirlst_split(t_token **head, int f1, int f2)
{
	t_token_section	*first;
	t_token			*temp;

	if (!head || !(*head))
		return (NULL);
	first = NULL;
	rdirlst_split_setstart((*head)->token_label, &(*head)->next->start_pos);
	temp = (*head)->next;
	(*head)->next = NULL;
	tokenlst_clear(head);
	*head = temp;
	while (temp && temp->next)
	{
		if (temp->next->token_label == f1 || temp->next->token_label == f2)
			rdirlst_cut(head, &temp, &first);
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

void	clear_section(t_token_section **head)
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
