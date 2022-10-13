/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/13 14:31:15 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

void	builtin_error(char *program, char *object, int errnum, t_metadata *data)
{
	char *print;
	char *message;

	data->exitstatus = EXIT_FAILURE;
	message = get_error_string(message, errnum);
	if (errnum == TOO_MANY)
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		return ;
	}
	print = NULL;
	print = ft_strjoin("minishell: ", program);
	print = ft_strjoin_free(print, object);
	print = ft_strjoin_free(print, message);
	if (!print)
	{
		write(STDERR_FILENO, "malloc fail in error\n", 21);
		exit(EXIT_FAILURE);
	}
	write(STDERR_FILENO, print, ft_strlen(print));
	free(print);
}

/*  

	We could inplemet a buffer of env var locations, like vectors do in cpp,
	if export then always 10 or 5 or so, keep a variable in meta to know how 
	many places are in use.

*/
bool	unset_var_not_valid(char *var)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(var[0]) || var[0] == '_'))
		return (true);
	while (var[i])
	{
		if (!ft_isalnum(var[i]))
			return (true);
		i++;
	}
	return (false);
}

void	padloper_unset(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int	i;
	int	j;

	i = 1;
	if (!cmd_list->cmd[1])
		return ;
	while(cmd_list->cmd[i])
	{
		if (unset_var_not_valid(cmd_list->cmd[i]))
		{
			builtin_error("unset: `", cmd_list->cmd[i], NOT_VALID, data);
			i++;
			continue ;
		}
		j = 0;
		while (data->padloper_envp[j])
		{
			if(!envcmp(data->padloper_envp[j], cmd_list->cmd[i]))
			{
				printf("!!unset var [%s]\n", cmd_list->cmd[i]);
				free(data->padloper_envp[j]);
				data->padloper_envp[j] = data->padloper_envp[data->envp_size - 1];
				data->padloper_envp[data->envp_size - 1] = NULL;
				data->envp_size--;
				data->env_updated = true;
				printf("last place [%s]\n", data->padloper_envp[data->envp_size - 1]);
				printf("swapped place [%s]\n", data->padloper_envp[j]);
			}
			j++;
		}
		i++;
	}
}
