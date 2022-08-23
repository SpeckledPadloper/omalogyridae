/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 15:44:38 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/05 15:04:36 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int argi)
{
	if (!(ft_isdigit(argi) || ft_isalpha(argi)))
		return (0);
	return (8);
}
