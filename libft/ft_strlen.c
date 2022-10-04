/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 13:32:03 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/02 13:50:25 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *args)
{
	int	len;

	len = 0;
	while (args[len] != '\0')
		len++;
	return (len);
}
