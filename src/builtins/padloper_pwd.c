/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_pwd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/01 16:11:37 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/executer.h"

void	padloper_pwd(t_metadata *data)
{
	fprintf(stderr, "check pwd\n");
	write(STDOUT_FILENO, "pwd go to pipe\n", 15);
	exit(0);
}
