/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 13:29:52 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/29 14:53:29 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include "../utils/hdr/token_utils.h"
#include <stdio.h>

void	link_expand_tokens(t_token **head, t_token **temp, t_token **expand)
{
	if (*temp == *head)
	{
		tokenlst_last(*expand)->next = (*temp)->next;
		*head = *expand;
		(*temp)->next = NULL;
		tokenlst_clear(temp);
	}
	else
	{
		tokenlst_cut_one(head, temp);
		tokenlst_last(*expand)->next = *temp;
		tokenlst_last(*head)->next = *expand;
	}
}
