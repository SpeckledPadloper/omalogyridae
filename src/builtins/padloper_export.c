/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/29 12:28:25 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	padloper_export(void)
{
	fprintf(stderr, "check export\n");
	write(STDOUT_FILENO, "export go to pipe\n", 16);
	exit(0);
}
