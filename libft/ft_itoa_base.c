/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/15 15:41:55 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:44:52 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

static size_t	buildlen(long long int nbr, unsigned int base)
{
	size_t	len;

	len = 1;
	if (nbr < 0)
		len++;
	while (nbr / base)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(long long int nbr, unsigned int base)
{
	size_t	len;
	char	*arr;

	if (base < 2 || base > 36)
		return (NULL);
	len = buildlen(nbr, base);
	arr = (char *)calloc((len + 1), sizeof(char));
	if (arr == NULL)
		return (NULL);
	if (nbr < 0)
	{
		arr[0] = '-';
		nbr *= -1;
	}
	len--;
	if (nbr == 0)
		arr[len] = BASE_STR[0];
	while (nbr)
	{
		arr[len] = BASE_STR[nbr % base];
		len--;
		nbr /= base;
	}
	return (arr);
}
