/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_cmd_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 14:56:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/05 17:25:14 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include <unistd.h>
#include "../../libft/libft.h"
#include "../utils/hdr/filelst_utils.h"
#include <stdlib.h>

#include <stdio.h>

t_exec_list_sim	*simple_cmdlst_last(t_exec_list_sim	**head)
{
	t_exec_list_sim	*temp;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	simple_cmd_add_back(t_exec_list_sim **head, t_exec_list_sim *new)
{
	if (head == NULL)
		return ;
	if ((*head) == NULL)
		(*head) = new;
	else
		simple_cmdlst_last(head)->next = new;
}

void	simple_cmd_clear(t_exec_list_sim **head)
{
	t_exec_list_sim	*itter;

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
