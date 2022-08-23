/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 13:46:59 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:47:30 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	offset;

	offset = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		offset++;
	}
	return (offset);
}
