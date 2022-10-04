/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 15:07:23 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/13 11:48:05 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			offset;
	unsigned char	*ts;

	offset = 0;
	ts = (unsigned char *)s;
	while (offset < n)
	{
		if (ts[offset] == (unsigned char)c)
			return (&ts[offset]);
		offset++;
	}
	return (0);
}
