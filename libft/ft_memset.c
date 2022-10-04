/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 10:46:36 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/12 11:55:14 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	offset;
	char	*temp;

	offset = 0;
	temp = (char *)s;
	while (offset < n)
	{
		temp[offset] = c;
		offset++;
	}
	return (s);
}
