/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 13:29:52 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/06 17:57:10 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include "../utils/hdr/token_utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void	link_expand_tokens(t_token **head, t_token **expand)
{
	t_token	*itterhead;
	t_token	*itterexp;
	t_token	*temp;

	if (!head || !expand)
		return ;
	itterhead = *head;
	itterexp = *expand;
	if ((*head)->token_label == EXPAND)
	{
		temp = (*head)->next;
		free(*head);
		(*head) = *expand;
		*expand = (*expand)->next;
	}
	while (itterhead->next)
	{
		if (itterhead->next->token_label == EXPAND)
		{
			printf("link expand tokens\n");
			temp = itterhead->next->next;
			free(itterhead->next);
			itterhead->next = NULL;
			exp_token_add_back(&itterexp, temp);
			exp_token_add_back(head, itterexp);
			itterexp = itterexp->next;
		}
		if (itterhead)
			itterhead = itterhead->next;
	}
}
