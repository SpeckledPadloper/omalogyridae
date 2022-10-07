/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/07 15:56:06 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

void	padloper_echo(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int i;
	bool no_newline_flag;

	i = 1;
	no_newline_flag = false;
	if (!cmd_list->cmd[1])
		printf("\n");
	else if (!ft_strcmp(cmd_list->cmd[1], "-n"))
	{
		no_newline_flag = true;
		i++;
	}
	while(cmd_list->cmd[i])
	{
		if (!cmd_list->cmd[i + 1])
		{
			printf("%s", cmd_list->cmd[i]);
			if (!no_newline_flag)
				printf("\n");
		}
		else
			printf("%s ", cmd_list->cmd[i]);
		i++;
	}
	return ;
}
