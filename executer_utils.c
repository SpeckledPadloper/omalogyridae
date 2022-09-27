/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/27 17:15:21 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "executer.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>

#include <errno.h>

void	set_buildin_array(t_metadata *data)
{
	data->buildins[0] = "echo";
	data->buildins[1] = "cd";
	data->buildins[2] = "pwd";
	data->buildins[3] = "export";
	data->fn_buildins[0] = &check_echo;
	data->fn_buildins[1] = &check_cd;
	data->fn_buildins[2] = &check_pwd;
	data->fn_buildins[3] = &check_export;
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_3d_array(char ***cmd_array)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_array[i])
	{
		j = 0;
		while (cmd_array[i][j])
		{
			free(cmd_array[i][j]);
			j++;
		}
		free(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}

bool	is_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

void	close_and_check(int fd)
{
	int	fail_check;

	fail_check = close(fd);
	if (fail_check == -1)
		print_error_exit("close", errno, EMPTY);
}
