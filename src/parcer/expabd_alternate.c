/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expabd_alternate.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 19:14:43 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/04 19:28:40 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include <stdbool.h>

void	expand_section(t_token_secton **head, char ***env, bool isredir)
{
	t_token_section	*temp;

	if (!head)
		return ;
	while (temp && temp->head)
	{
		if (temp->head->start_pos = -1)
		{
			temp->head->token_label = RDIR_DOUBLE;
			temp = temp->next;
		}
		else
			expand_tokenlst(&temp, env, isredir);
	}
}
