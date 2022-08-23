/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 12:35:45 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:47:03 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			offset;
	unsigned char	*tdest;
	const char		*tsrc;

	offset = 0;
	tdest = (unsigned char *)dest;
	tsrc = (const char *)src;
	while (offset < n)
	{
		tdest[offset] = tsrc[offset];
		offset++;
		if (tdest[offset - 1] == (unsigned char)c)
			return (&tdest[offset]);
	}
	return (0);
}
