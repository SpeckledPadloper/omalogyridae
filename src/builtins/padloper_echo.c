/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/29 12:05:35 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	padloper_echo(void)
{
	fprintf(stderr, "check echo\n");
	write(STDOUT_FILENO, "echo go to pipe\n", 16);
	exit(0);
}
