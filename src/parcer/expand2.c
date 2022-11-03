/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 13:29:52 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/03 14:08:02 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include "../utils/hdr/token_utils.h"
#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>
#include "../tests/tests.h"

void	link_expand_tokens(t_token **head, t_token **expand)
{
	t_token	*itterhead;
	t_token	*itterexp;
	t_token	*temp;
	t_token	*temp2;

	if (!head || !expand || !(*expand))
		return ;
	if ((*head) && (*head)->token_label == EXPAND)
	{
		if ((*expand)->token_value == NULL)
			(*head) = (*head)->next;
		else
		{
			temp = (*head)->next;
			temp2 = (*expand)->next;
			if ((*head)->token_value)
				free((*head)->token_value);
			free(*head);
			(*head) = (*expand);
			(*head)->next = temp;
			(*expand) = temp2;
		}
	}
	itterhead = *head;
	itterexp = *expand;
	while (itterhead && itterhead->next)
	{
		if (itterhead->next->token_label == EXPAND)
		{
			temp = itterhead->next->next;
			if (itterhead->next->token_value)
				free(itterhead->next->token_value);
			free(itterhead->next);
			itterhead->next = itterexp;
			if (!itterexp)
				break ;
			temp2 = itterexp->next;
			itterhead->next->next = temp;
			itterexp = temp2;
		}
		itterhead = itterhead->next;
	}
}
