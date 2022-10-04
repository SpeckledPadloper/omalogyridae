/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 13:59:18 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/09 11:27:25 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*s3;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s3 = (char *)malloc(len * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	ft_strlcpy(s3, (char *)s1, (ft_strlen((char *)s1) + 1));
	ft_strlcat(s3, (char *)s2, len);
	return (s3);
}
