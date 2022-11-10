/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_cmd_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 14:56:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 14:43:05 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include "../../libft/libft.h"
#include "../utils/hdr/filelst_utils.h"
#include <stdlib.h>

int	tokenlst_len(t_token *head)
{
	t_token	*itter;
	int		len;

	len = 0;
	itter = head;
	while (itter)
	{
		len++;
		itter = itter->next;
	}
	return (len);
}

t_simple_cmd	*simple_cmdlst_last(t_simple_cmd	**head)
{
	t_simple_cmd	*temp;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	simple_cmd_add_back(t_simple_cmd **head, t_simple_cmd *new)
{
	if (head == NULL)
		return ;
	if ((*head) == NULL)
		(*head) = new;
	else
		simple_cmdlst_last(head)->next = new;
}

void	simple_cmd_clear(t_simple_cmd **head)
{
	t_simple_cmd	*itter;

	if (!head)
		return ;
	itter = *head;
	while (itter)
	{
		*head = (*head)->next;
		ft_free_split(itter->cmd);
		filelst_clear(itter->infile_list);
		filelst_clear(itter->outfile_list);
		free(itter);
		itter = *head;
	}
	*head = NULL;
}
