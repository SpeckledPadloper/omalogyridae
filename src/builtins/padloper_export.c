/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/13 14:47:46 by lwiedijk      ########   odam.nl         */
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

char	*export_strcpy(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '=')
		{
			dest[j] = src[i];
			dest[j + 1] = '"';
			i++;
			j += 2;
		}
		if (src[i] == '\0')
			break ;
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '"';
	dest[j + 1] = '\0';
	if (i == j)
		dest[j] = '\0';
	return (dest);
}

void	populate_export(int size, char **src, char **dst)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (src[i][j])
			j++;
		dst[i] = (char *)malloc(sizeof(char) * j + 3);
		if (!dst)
			print_error_exit("malloc", errno, EXIT_FAILURE);
		export_strcpy(dst[i], src[i]);
		i++;
	}
	dst[i] = NULL;
}

bool	export_var_not_valid(char *var)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(var[0]) || var[0] == '_'))
		return (true);
	while (var[i] && var[i] != '=')
	{
		if (!(ft_isalnum(var[i]) || var[i] == '='))
			return (true);
		i++;
	}
	return (false);
}

void	add_var(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char	**temp_env;
	bool	found;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (cmd_list->cmd[i])
	{
		if (export_var_not_valid(cmd_list->cmd[i]))
		{
			builtin_error("export: `", cmd_list->cmd[i], NOT_VALID, data);
			i++;
			continue ;
		}
		data->env_updated = true;
		j = 0;
		found = false;
		while (data->padloper_envp[j])
		{
			if (!envcmp(data->padloper_envp[j], cmd_list->cmd[i]))
			{
				found = true;
				if (env_has_value(cmd_list->cmd[i]))
					add_env(data->padloper_envp, cmd_list->cmd[i], j);
				break ;
			}
			j++;
		}
		if (found)
		{
			i++;
			continue ;
		}
		printf("!!add new variable: %s\n", cmd_list->cmd[i]);
		temp_env = allocate_env(data->padloper_envp, &(data->envp_size), false, true);
		env_pointer_cpy(data->envp_size, data->padloper_envp, temp_env);
		free(data->padloper_envp);
		data->padloper_envp = temp_env;
		add_env(data->padloper_envp, cmd_list->cmd[i], data->envp_size - 1);
		data->padloper_envp[data->envp_size] = NULL;
		i++;
		printf("env size end = [%d]\n", data->envp_size);
	}
}

void	sort_env(t_metadata *data)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < data->envp_size)
	{
		j = 1 + i;
		while (j < data->envp_size)
		{
			if (envcmp(data->sorted_print_export[i],
					data->sorted_print_export[j]) > 0)
			{
				temp = data->sorted_print_export[j];
				data->sorted_print_export[j] = data->sorted_print_export[i];
				data->sorted_print_export[i] = temp;
			}
			j++;
		}
		i++;
	}
}

void	padloper_export(t_metadata *data, t_exec_list_sim *cmd_list)
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
		data->sorted_print_export = allocate_env
			(data->padloper_envp, &(data->envp_size), false, false);
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
