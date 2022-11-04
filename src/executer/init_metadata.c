/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_metadata.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/04 14:56:48 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>

#include <errno.h>

int	ft_sim_lstsize(t_exec_list_sim *lst)
{
	t_exec_list_sim	*temp;
	int				count;

	temp = lst;
	count = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

void	set_buildin_array(t_metadata *data)
{
	data->buildins[0] = "echo";
	data->buildins[1] = "cd";
	data->buildins[2] = "pwd";
	data->buildins[3] = "export";
	data->buildins[4] = "unset";
	data->buildins[5] = "env";
	data->buildins[6] = "exit";
	data->fn_buildins[0] = &padloper_echo;
	data->fn_buildins[1] = &padloper_cd;
	data->fn_buildins[2] = &padloper_pwd;
	data->fn_buildins[3] = &padloper_export;
	data->fn_buildins[4] = &padloper_unset;
	data->fn_buildins[5] = &padloper_env;
	data->fn_buildins[6] = &padloper_exit;
}

void	init_metadata(t_metadata *data, t_fd_list *fd_list, char **envp)
{
	data->envp_space = 0;
	data->padloper_envp = new_padloper_envp(envp, data, &(data->envp_size));
	data->sorted_print_export = NULL;
	data->env_updated = true;
	data->exitstatus = 0;
	g_exitstatus = 0;
	set_buildin_array(data);
}

void	reset_metadata(t_metadata *data, t_fd_list *fd_list, char **envp)
{
	ft_bzero(fd_list, sizeof(t_fd_list));
	data->fd_list = fd_list;
	data->child_count = 0;
	data->cmd_count = 0;
	data->lastpid = 0;
	data->exitstatus = 0;
	g_exitstatus = 0;
}
