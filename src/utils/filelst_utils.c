/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filelst_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 13:12:30 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/26 14:19:41 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include <stdlib.h>

t_file	*filelst_new(char *content, int flag)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		exit(EXIT_FAILURE);
	new->filename = content;
	new->mode = flag;
	new->next = NULL;
	return (new);
}

t_file	*filelst_last(t_file *head)
{
	t_file	*ret;

	if (!head)
		return (NULL);
	ret = head;
	while (ret->next)
		ret = ret->next;
}

void	filelst_add_back(t_file **head, t_file *new)
{
	if (!head || !(*head) || !new)
		return ;
	filelst_last(*head)->next = new;
}

void	filelst_clear(t_file *head)
{
	t_file	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}
