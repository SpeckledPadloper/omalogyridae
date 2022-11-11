/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/11 09:53:28 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

bool	unset_var_not_valid(char *var)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(var[0]) || var[0] == '_'))
		return (true);
	while (var[i])
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (true);
		i++;
	}
	return (false);
}

void	unset_var(t_metadata *data, int pos)
{
	free(data->padloper_envp[pos]);
	data->padloper_envp[pos]
		= data->padloper_envp[data->envp_size - 1];
	data->envp_size--;
	data->padloper_envp[data->envp_size] = NULL;
	data->env_updated = true;
}

void	padloper_unset(t_metadata *data, t_simple_cmd *cmd_list)
{
	int	i;
	int	pos;

	i = 1;
	if (!cmd_list->cmd[1])
		return ;
	while (cmd_list->cmd[i])
	{
		if (unset_var_not_valid(cmd_list->cmd[i]))
		{
			builtin_error("unset: `", cmd_list->cmd[i], NOT_VALID, data);
			i++;
			continue ;
		}
		pos = has_var(data->padloper_envp, cmd_list->cmd[i]);
		if (pos)
			unset_var(data, pos);
		i++;
	}
}
