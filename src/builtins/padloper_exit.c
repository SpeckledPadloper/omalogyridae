/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/29 12:35:58 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	padloper_exit(void)
{
	fprintf(stderr, "check exit\n");
	write(STDOUT_FILENO, "exit go to pipe\n", 16);
	exit(0);
}
