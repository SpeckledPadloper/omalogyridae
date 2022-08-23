/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdelone.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 14:09:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:45:38 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst == NULL)
		return ;
	temp = lst->next;
	del(lst->content);
	free(lst);
	lst = temp;
	return ;
}
