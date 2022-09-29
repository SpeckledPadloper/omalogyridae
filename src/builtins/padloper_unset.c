/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/29 12:29:06 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	padloper_unset(void)
{
	fprintf(stderr, "check unset\n");
	write(STDOUT_FILENO, "unset go to pipe\n", 16);
	exit(0);
}
