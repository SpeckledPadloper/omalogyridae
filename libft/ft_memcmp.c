/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 15:37:29 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/12 11:54:55 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	offset;
	char	*ts1;
	char	*ts2;

	offset = 0;
	ts1 = (char *)s1;
	ts2 = (char *)s2;
	while (offset < n)
	{
		if (ts1[offset] != ts2[offset])
			return ((unsigned char)ts1[offset] - (unsigned char)ts2[offset]);
		offset++;
	}
	return (0);
}
