/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 15:08:46 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/20 15:23:31 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	mem_all_error(void)
{
	write(2, "memory allocation error\n", 24);
	exit(EXIT_FAILURE);
}
