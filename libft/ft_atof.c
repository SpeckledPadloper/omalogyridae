/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 14:16:34 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/10/14 17:42:31 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static double	pow(double nbr, double power)
{
	int		i;
	double	result;

	i = 0;
	result = 1;
	while (i < power)
	{
		result *= nbr;
		i++;
	}
	return (result);
}

static double	get_digit(const char *nptr, int *offset)
{
	double	result;

	result = 0;
	while (ft_isdigit(nptr[*offset]))
	{
		result *= 10;
		result += (nptr[*offset] - '0');
		(*offset)++;
	}
	return (result);
}

static double	get_decimal(const char *nptr, int offset)
{
	double	result;
	int		decimal;

	result = 0;
	decimal = 1;
	while (decimal <= 7 && ft_isdigit(nptr[offset + decimal]))
	{
		result += (nptr[offset + decimal] - '0') / pow(10, decimal);
		decimal++;
	}
	return (result);
}

double	ft_atof(const char *nptr)
{
	int		offset;
	double	result;
	int		negative;

	offset = 0;
	result = 0;
	negative = 1;
	while ((nptr[offset] >= '\t' && nptr[offset] <= '\r') \
			|| nptr[offset] == ' ')
		offset++;
	if (nptr[offset] == '+')
		offset++;
	else if (nptr[offset] == '-')
	{
		negative *= -1;
		offset++;
	}
	result += get_digit(nptr, &offset);
	if (nptr[offset] != '.')
		return (result * negative);
	result += get_decimal(nptr, offset);
	return (result * negative);
}
