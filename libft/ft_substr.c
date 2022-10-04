/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 13:31:26 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/20 16:54:43 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sstr;

	if (s == NULL)
		return (NULL);
	sstr = (char *)malloc((len + 1) * sizeof(char));
	if (sstr == NULL)
		return (NULL);
	if (start > ft_strlen((char *)s))
		ft_strlcpy(sstr, "", len + 1);
	else
		ft_strlcpy(sstr, (s + start), len + 1);
	return (sstr);
}
