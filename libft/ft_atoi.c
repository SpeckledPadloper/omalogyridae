/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 15:34:34 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/25 15:01:23 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		offset;
	long	result;
	int		negative;

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
