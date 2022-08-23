/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 11:00:28 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:44:39 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	buildlen(size_t len, int n)
{
	if (n < 0)
		len++;
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	ln;
	char	*arr;

	len = 1;
	ln = n;
	len = buildlen(len, n);
	arr = (char *)malloc((len + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	if (ln < 0)
	{
		arr[0] = '-';
		ln *= -1;
	}
	arr[len] = '\0';
	len--;
	while (ln / 10)
	{
		arr[len] = (ln % 10) + '0';
		len--;
		ln /= 10;
	}
	arr[len] = (ln % 10) + '0';
	return (arr);
}
