/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_pwd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/29 12:26:55 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	padloper_pwd(void)
{
	fprintf(stderr, "check pwd\n");
	write(STDOUT_FILENO, "pwd go to pipe\n", 16);
	exit(0);
}
