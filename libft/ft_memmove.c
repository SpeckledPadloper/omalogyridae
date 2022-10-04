/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 14:35:47 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:56:49 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	offset;

	offset = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest >= src)
	{
		while (0 < n)
		{
			((char *)dest)[n - 1] = ((char *)src)[n - 1];
			n--;
		}
	}
	else
	{
		while (offset < n)
		{
			((char *)dest)[offset] = ((char *)src)[offset];
			offset++;
		}
	}
	return ((void *)dest);
}
