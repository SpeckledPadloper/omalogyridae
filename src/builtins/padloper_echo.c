/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/26 16:02:38 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"


bool	check_option(t_exec_list_sim *cmd_list, int *i)
{
	int		j;
	bool	no_newline_flag;

	no_newline_flag = false;
	while (cmd_list->cmd[*i] && !ft_strncmp(cmd_list->cmd[*i], "-n", 2))
	{
		j = 1;
		while(cmd_list->cmd[*i][j] && cmd_list->cmd[*i][j] == 'n')
			j++;
		if (cmd_list->cmd[*i][j] && cmd_list->cmd[*i][j] != 'n')
			break;
		no_newline_flag = true;
		(*i)++;
	}
	return (no_newline_flag);
}

void	padloper_echo(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int		i;
	int		j;
	bool	no_newline_flag;

	i = 1;
	no_newline_flag = false;
	if (!cmd_list->cmd[1])
		printf("\n");
	no_newline_flag = check_option(cmd_list, &i);
	while (cmd_list->cmd[i])
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
