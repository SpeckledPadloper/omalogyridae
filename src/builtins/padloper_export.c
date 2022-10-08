/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/08 12:13:15 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

/*  

wat unset betreft:
houd een meta count bij n = number of strings in envp
bij unset met parameter:
strcmp tot aan unset, dan swop current i met n (naar laatste plaats),
copyeer alles naar nieuwe array behalve laatste plaats
update n naar n--

bij export:
update n naar n++;
reallocate,

sort by moving poitners ?
alloceer alleen een 2d pointer array met pointers naar env array in gesorteerde volgorde?

sort array

*/

void export_error(char *error_object, int error_case)
{
	if (error_case == NOT_SUPPORTED)
		printf("options in export are not supported by Speckled Padloper\n");
	else if (error_case == NOT_VALID)
		printf("minishell: export: '%s': not a valid identifier\n", error_object);
}

int	envcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '=' || s2[i] != '=')
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

int varlen(char *str)
{
	int i;

	i = 1;
	while(str[i] != '=')
		i++;
	return(i);
}

void	add_var(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char **temp_env;
	bool found;
	int i;
	int j;

	i = 1;
	j = 0;
	// bash: export: `?': not a valid identifier
	// protect "not option with no '-' "
	while(cmd_list->cmd[i])
	{
		printf("hallo cmd is : %s\n", cmd_list->cmd[i]);
		j = 0;
		found = false;
		while(data->padloper_envp[j])
		{
			if (!envcmp(data->padloper_envp[j], cmd_list->cmd[i])
				|| envcmp(data->padloper_envp[j], cmd_list->cmd[i]) == EXISTING_VAR_HAS_NO_VALUE)
			{
				found = true;
				data->padloper_envp[j] = cmd_list->cmd[i];
				break ;
			}
			else if (envcmp(data->padloper_envp[j], cmd_list->cmd[i]) == EXPORTED_VAR_HAS_NO_VALUE)
			{
				found = true;
				break ;
			}
			j++;
		}
		if (found)
		{
			i++;
			continue;
		}
		printf("!!add new variable: %s\n", cmd_list->cmd[i]);
		temp_env = allocate_env(data->padloper_envp, &(data->envp_size), false, true);
		free(data->padloper_envp);//free whole array!!;
		data->padloper_envp = temp_env;
		add_env(data->padloper_envp, cmd_list->cmd[i], data->envp_size - 1);
		i++;
	}
	
}

void	padloper_export(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char **sorted_env;
	char *temp;
	int i;
	int j;

	i = 0;
	if (cmd_list->cmd[1])
		add_var(data, cmd_list);
	sorted_env = (char **)malloc(sizeof(char*) * data->envp_size + 1);
	while(i < data->envp_size)
	{
		sorted_env[i] = data->padloper_envp[i];
		i++;
	}
	sorted_env[i] = NULL;
	i = 0;
	while(i < data->envp_size)
	{
		j = 1 + i;
		while(j < data->envp_size)
		{
			if (envcmp(sorted_env[i], sorted_env[j]) > 0)
			{
				temp = sorted_env[j];
				sorted_env[j] = sorted_env[i];
				sorted_env[i] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < data->envp_size)
	{
		printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	i = 0;
	while (i < data->envp_size)
	{
		printf("original: %s\n", data->padloper_envp[i]);
		i++;
	}
	return ;
}
