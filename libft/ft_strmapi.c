/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 19:45:41 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/12 12:18:14 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*mapi;

	i = 0;
	if (s == NULL)
		return (NULL);
	mapi = (char *)malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (mapi == NULL)
		return (0);
	while (i < ft_strlen((char *)s))
	{
		mapi[i] = (*f)(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}
