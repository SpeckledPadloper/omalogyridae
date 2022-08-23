/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 14:49:17 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/16 12:28:38 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup;

	len = (ft_strlen(s) + 1);
	dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, len);
	return (dup);
}
