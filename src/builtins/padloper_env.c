/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/09 12:35:48 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "../../libft/libft.h"
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"

void	padloper_env(t_metadata *data, t_simple_cmd *cmd_list)
{
	int	i;

	if (cmd_list->cmd[1])
	{
		builtin_error("env: ", cmd_list->cmd[1], NOT_SUPPORTED_BOTH, data);
		return ;
	}
	if (!data || !data->padloper_envp)
		print_error_exit("padloper_env", EMPTY, EXIT_FAILURE);
	i = 0;
	while (data->padloper_envp[i])
	{
		if (env_has_value(data->padloper_envp[i]))
			printf("%s\n", data->padloper_envp[i]);
		i++;
	}
	return ;
}
