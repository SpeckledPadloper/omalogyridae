/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 12:15:39 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/12 17:06:19 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		offset;
	char		*tdest;
	const char	*tsrc;

	offset = 0;
	if (dest == 0 && src == 0)
		return (0);
	tdest = (char *)dest;
	tsrc = (const char *)src;
	while (offset < n)
	{
		tdest[offset] = tsrc[offset];
		offset++;
	}
	return (dest);
}
