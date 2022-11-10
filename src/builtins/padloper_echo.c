/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/10 14:25:59 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

bool	check_option(t_simple_cmd *cmd_list, int *i)
{
	int		j;
	bool	no_newline_flag;

	no_newline_flag = false;
	while (cmd_list->cmd[*i] && !ft_strncmp(cmd_list->cmd[*i], "-n", 2))
	{
		j = 1;
		while (cmd_list->cmd[*i][j] && cmd_list->cmd[*i][j] == 'n')
			j++;
		if (cmd_list->cmd[*i][j] && cmd_list->cmd[*i][j] != 'n')
			break ;
		no_newline_flag = true;
		(*i)++;
	}
	return (no_newline_flag);
}

void	padloper_echo(t_metadata *data, t_simple_cmd *cmd_list)
{
	int		i;
	bool	no_newline_flag;

	i = 1;
	(void)data;
	no_newline_flag = false;
	if (!cmd_list->cmd[1])
		printf("\n");
	no_newline_flag = check_option(cmd_list, &i);
	while (cmd_list->cmd[i])
	{
		if (!cmd_list->cmd[i + 1])
		{
			write(1, cmd_list->cmd[i], ft_strlen(cmd_list->cmd[i]));
			if (!no_newline_flag)
				write(1, "\n", 1);
		}
		else
		{
			write(1, cmd_list->cmd[i], ft_strlen(cmd_list->cmd[i]));
			write(1, " ", 1);
		}
		i++;
	}
	return ;
}
