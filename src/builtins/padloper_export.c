/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/09 14:12:50 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

void	add_new_var_to_env(t_metadata *data, t_simple_cmd *cmd_list, int pos)
{
	char	**temp_env;

	if (!(data->envp_space > data->envp_size))
	{
		temp_env = allocate_env(data->padloper_envp,
				data, true);
		env_pointer_cpy(data->envp_size, data->padloper_envp, temp_env);
		free(data->padloper_envp);
		data->padloper_envp = temp_env;
	}
	else
		data->envp_size++;
	add_env(data->padloper_envp, cmd_list->cmd[pos], data->envp_size - 1);
	data->padloper_envp[data->envp_size] = NULL;
}

static void	add_value_existing_key(t_metadata *data,
			t_simple_cmd *cmd_list, int pos, int i)
{
	if (env_has_value(cmd_list->cmd[i]))
	{
		free(data->padloper_envp[pos]);
		add_env(data->padloper_envp, cmd_list->cmd[i], pos);
	}
}

void	add_var(t_metadata *data, t_simple_cmd *cmd_list)
{
	int		i;
	int		pos;

	i = 1;
	while (cmd_list->cmd[i])
	{
		if (export_var_not_valid(cmd_list->cmd[i]))
		{
			builtin_error("export: `", cmd_list->cmd[i], NOT_VALID, data);
			i++;
			continue ;
		}
		data->env_updated = true;
		pos = has_var(data->padloper_envp, cmd_list->cmd[i]);
		if (pos)
		{
			add_value_existing_key(data, cmd_list, pos, i);
			i++;
			continue ;
		}
		add_new_var_to_env(data, cmd_list, i);
		i++;
	}
}

void	padloper_export(t_metadata *data, t_simple_cmd *cmd_list)
{
	int	i;

	if (cmd_list->cmd[1])
	{
		add_var(data, cmd_list);
		return ;
	}
	if (data->env_updated)
	{
		if (data->sorted_print_export)
			free_2d_array(data->sorted_print_export);
		data->sorted_print_export = allocate_env \
			(data->padloper_envp, data, false);
		populate_export(data->envp_size, data->padloper_envp,
			data->sorted_print_export);
		sort_env(data);
		data->env_updated = false;
	}
	i = 0;
	while (i < data->envp_size)
	{
		printf("declare -x %s\n", data->sorted_print_export[i]);
		i++;
	}
}
