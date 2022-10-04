/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 12:50:07 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/01/18 13:43:36 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	offset;
	size_t			len;

	offset = 0;
	start = 0;
	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	len = ft_strlen((char *)s1);
	while (offset < ft_strlen((char *)set) && len != 0)
	{
		if (!ft_strncmp((s1 + start + len - 1), (set + offset), 1) \
				|| !ft_strncmp((s1 + start), (set + offset), 1))
		{
			if (!ft_strncmp((s1 + start), (set + offset), 1))
				start++;
			len--;
			offset = 0;
			continue ;
		}
		offset++;
	}
	return (ft_substr(s1, start, len));
}
