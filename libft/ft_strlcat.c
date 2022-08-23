/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:38:33 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/14 17:33:54 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	offdst;
	size_t	offsrc;
	size_t	lendst;
	size_t	lensrc;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	offdst = lendst;
	offsrc = 0;
	if (size == 0)
		return (lensrc);
	if (lendst >= size)
		return (lensrc + size);
	while ((src[offsrc] != '\0') && (offdst < (size - 1)))
	{
		dst[offdst] = src[offsrc];
		offdst++;
		offsrc++;
	}
	if (offdst < size)
	{
		dst[offdst] = '\0';
		offdst++;
	}
	return (lendst + lensrc);
}
