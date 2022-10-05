/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/05 15:47:11 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/executer.h"
#include "../hdr/structs.h"

void	padloper_unset(t_metadata *data, t_exec_list_sim *cmd_list)
{
	if (!data || !cmd_list)
	{
		fprintf(stderr, "Parameters are NULL");
		exit(1);
	}
	fprintf(stderr, "check unset\n");
	write(STDOUT_FILENO, "unset go to pipe\n", 17);
	exit(0);
}
