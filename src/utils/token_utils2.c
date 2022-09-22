/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:19:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/21 14:30:15 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/hdr/lexer.h"
#include <stdlib.h>
#include "../hdr/structs.h"
#include "../error/error.h"

#include <stdio.h>

void	tokenlst_clear(t_token **head)
{
	t_token	*temp;

	if (*head == NULL)
		return ;
	temp = *head;
	while (temp->next)
	{
		*head = temp->next;
		free(temp->token_value);
		free(temp);
		temp = *head;
	}
	free(temp->token_value);
	free(temp);
	*head = NULL;
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

void	add_section_to_list(t_token_section **first, t_token *head)
{
	t_token_section	*new;

	new = new_token_section(head);
	if (*first == NULL)
		*first = new;
	else
		token_section_last(*first)->next = new;
}

void	cut_token(t_token **head, t_token **tail)
{
	*head = (*tail)->next->next;
	free((*tail)->next);
	(*tail)->next = NULL;
}

t_token_section	*tokenlst_split(t_token *head)
{
	t_token_section	*first;
	t_token			*temp;

	first = NULL;
	temp = head;
	while (temp && temp->next)
	{
		if (temp->next->token_label == PIPE)
		{
			add_section_to_list(&first, head);
			cut_token(&head, &temp);
			temp = head;
		}
		else if (temp)
			temp = temp->next;
	}
	add_section_to_list(&first, head);
	return (first);
}
