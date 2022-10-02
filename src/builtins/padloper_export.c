/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/02 13:27:17 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/executer.h"

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

void	add_var(t_metadata *data, t_exec_list_sim *cmd_list)
{
	printf("hallo add variable: %s\n", cmd_list->cmd[1]);
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
	exit(0);
}
