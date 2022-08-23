/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 11:36:10 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:45:23 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*elem;

	if (lst == NULL || (*f) == NULL)
		return (NULL);
	map = NULL;
	while (lst != NULL)
	{
		elem = ft_lstnew((*f)(lst->content));
		if (elem == NULL)
		{
			ft_lstclear(&map, (*del));
			return (NULL);
		}
		ft_lstadd_back(&map, elem);
		lst = lst->next;
	}
	return (map);
}
