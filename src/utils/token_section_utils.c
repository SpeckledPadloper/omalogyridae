/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_section_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 19:45:39 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/26 19:56:01 by mteerlin      ########   odam.nl         */
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

void	add_section_to_list(t_token_section **first, t_token *head)
{
	t_token_section	*new;

	new = new_token_section(head);
	if (*first == NULL)
		*first = new;
	else
		token_section_last(*first)->next = new;
}

t_token_section	*command_split(t_token **head)
{
	t_token_section	*first;
	t_token			*temp;
	int				sep;

	if (!head || !(*head))
		return (NULL);
	first = NULL;
	sep = 1;
	temp = *head;
	if (temp->next)
		sep = set_separation_limit(temp);
	while (temp && temp->next)
	{
		if (temp->next->start_pos - temp->end_pos <= sep)
		{
			add_section_to_list(&first, *head);
			*head = temp->next;
		}
		temp = temp->next;
	}
	return (first);
}

t_token_section	*rdirlst_split(t_token **head, int f1, int f2)
{
	t_token_section	*first;
	t_token			*temp;
	int				state;

	if (!head || !(*head))
		return (NULL);
	first = NULL;
	state = (*head)->token_label;
	temp = (*head)->next;
	(*head)->next = NULL;
	tokenlst_clear(head);
	*head = temp;
	(*head)->token_label = state;
	while (temp && temp->next)
	{
		if (temp->next->token_label == f1 || temp->next->token_label == f2)
		{
			state = temp->next->token_label;
			add_section_to_list(&first, *head);
			cut_token(head, &temp);
			temp = *head;
			(*head)->token_label = state;
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
