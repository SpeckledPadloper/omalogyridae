/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/12 15:11:46 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

bool	var_not_numeric(char *var)
{
	int i;

	i = 0;
	while(var[i])
	{
		if (!ft_isdigit(var[i]))
			return (true);
		i++;
	}
	return (false);
}

void	padloper_exit(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int exitcode;

	if (data->cmd_count == 1)
		printf("exit (buildin)\n");
	if (!cmd_list->cmd[1])
		exit(EXIT_SUCCESS);
	if (var_not_numeric(cmd_list->cmd[1]))
	{
		builtin_error("exit: ", cmd_list->cmd[1], NOT_NUMERIC, data);
		data->exitstatus = 255;
	}
	else if (cmd_list->cmd[2])
		builtin_error("exit", NULL, TOO_MANY, data);
	else
	{
		exitcode = 0;
		exitcode = ft_atoi(cmd_list->cmd[1]);
		data->exitstatus = exitcode;
	}
	exit(data->exitstatus);
}
