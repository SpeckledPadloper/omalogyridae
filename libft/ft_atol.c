/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 15:48:50 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/09/07 15:49:40 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atol(const char *nptr)
{
	int				offset;
	long long int	result;
	int				negative;

	offset = 0;
	result = 0;
	negative = 1;
	while ((nptr[offset] >= '\t' && nptr[offset] <= '\r') || nptr[offset] == 32)
		offset++;
	if (nptr[offset] == '+')
		offset++;
	else if (nptr[offset] == '-')
	{
		negative *= -1;
		offset++;
	}
	while (ft_isdigit(nptr[offset]))
	{
		result *= 10;
		result += (nptr[offset] - '0');
		offset++;
	}
	return (result * negative);
}
