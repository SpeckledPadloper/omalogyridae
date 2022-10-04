/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/04 15:31:17 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/executer.h"

void	padloper_cd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	if (!data || !cmd_list)
	{
		fprintf(stderr, "Parameters are NULL");
		exit(1);
	}
	fprintf(stderr, "check cd\n");
	write(STDOUT_FILENO, "cd go to pipe\n", 14);
	exit(0);
}
