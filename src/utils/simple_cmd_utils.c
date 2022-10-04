/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_cmd_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 14:56:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/01 20:15:09 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include <unistd.h>
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
