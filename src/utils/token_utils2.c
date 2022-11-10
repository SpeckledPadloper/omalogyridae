/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:19:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 12:48:53 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../hdr/structs.h"
#include "../hdr/ms_enums.h"
#include "hdr/token_utils.h"
#include "../../libft/libft.h"

void	tokenlst_clear(t_token **head)
{
	t_token	*temp;

	if (head == NULL || (*head) == NULL)
		return ;
	while ((*head) != NULL)
	{
		temp = (*head)->next;
		if ((*head)->token_value != NULL)
			free((*head)->token_value);
		free(*head);
		(*head) = temp;
	}
}

void	tokenlst_cut_one(t_token **head, t_token **target)
{
	t_token	*temp;

	if (!head || !target)
		return ;
	temp = (*head);
	while (temp)
	{
		if (temp->next == *target)
		{
			(*target) = (*target)->next;
			free(temp->next->token_value);
			free(temp->next);
			temp->next = 0;
			break ;
		}
		temp = temp->next;
	}
}

void	cut_token(t_token **head, t_token **tail)
{
	*head = (*tail)->next->next;
	if ((*tail)->next->token_value)
		free((*tail)->next->token_value);
	free((*tail)->next);
	(*tail)->next = NULL;
}

t_token	*exp_new_token(char *value)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit(EXIT_FAILURE);
	new->token_value = value;
	new->token_label = EXPAND;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_token **head, t_token *new)
{
	if (!head)
		exit(EXIT_FAILURE);
	if (!(*head))
		*head = new;
	else
		tokenlst_last(*head)->next = new;
}
