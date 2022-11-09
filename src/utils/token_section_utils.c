/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_section_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 19:45:39 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 21:03:15 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../hdr/structs.h"
#include "../hdr/ms_enums.h"
#include "hdr/token_utils.h"
#include "../parcer/hdr/separate.h"

t_token_section	*new_token_section(t_token *head)
{
	t_token_section	*new;

	new = malloc(sizeof(t_token_section));
	if (!new)
		exit(EXIT_FAILURE);
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

int	token_section_len(t_token_section *head)
{
	t_token_section	*temp;
	int				len;

	temp = head;
	len = 0;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

void	add_section_to_list(t_token_section **first, t_token *head)
{
	t_token_section	*new;

	if (first == NULL)
		return ;
	new = new_token_section(head);
	if (*first == NULL)
		*first = new;
	else
		token_section_last(*first)->next = new;
}

t_token_section	*cmdlst_split(t_token **head)
{
	t_token_section	*first;
	t_token			*temp;
	int				sep;

	if (!head || !*head)
		return (NULL);
	first = NULL;
	sep = 1;
	temp = *head;
	while (temp && temp->next)
	{
		sep = set_separation_limit(temp);
		if ((temp->next->start_pos - temp->end_pos) > sep)
		{
			add_section_to_list(&first, *head);
			*head = temp->next;
			temp->next = NULL;
			temp = *head;
		}
		else
			temp = temp->next;
	}
	add_section_to_list(&first, *head);
	return (first);
}
