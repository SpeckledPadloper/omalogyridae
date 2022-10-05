/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/05 15:47:39 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/executer.h"
#include "../hdr/structs.h"

void	padloper_exit(t_metadata *data, t_exec_list_sim *cmd_list)
{
	if (!data || !cmd_list)
	{
		fprintf(stderr, "Parameters are NULL");
		exit(1);
	}
	fprintf(stderr, "check exit\n");
	write(STDOUT_FILENO, "exit go to pipe\n", 16);
	exit(0);
}
