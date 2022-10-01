/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/01 16:11:02 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/executer.h"

void	padloper_exit(t_metadata *data)
{
	fprintf(stderr, "check exit\n");
	write(STDOUT_FILENO, "exit go to pipe\n", 16);
	exit(0);
}
