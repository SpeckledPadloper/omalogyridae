/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:19:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/18 19:30:29 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/lexer.h"
#include <stdlib.h>
#include "../hdr/structs.h"

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
