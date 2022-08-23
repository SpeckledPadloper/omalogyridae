/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 19:44:32 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:50:33 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	offset;

	offset = 0;
	if (n == 0)
		return (0);
	while (offset < n)
	{
		if (s1[offset] != s2[offset])
		{
			return ((unsigned char)s1[offset] - (unsigned char)s2[offset]);
		}
		if (s1[offset] == '\0' || s2[offset] == '\0')
			break ;
		offset++;
	}
	return (0);
}
