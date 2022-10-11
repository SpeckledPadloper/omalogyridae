/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/11 21:26:32 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

void	print_argument_error(char *program, char *errorobject)
{
	char *print;

	print = NULL;
	print = ft_strjoin("minishell: ", program);
	print = ft_strjoin_free(print, errorobject);
	print = ft_strjoin_free(print, "': not a valid identifier\n");
	if (!print)
	{
		write(STDERR_FILENO, "malloc fail in error\n", 21);
		exit(EXIT_FAILURE);
	}
	write(STDERR_FILENO, print, ft_strlen(print));
	free(print);
}

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

int	unset_envcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (!(s1[i] == '=' || s1[i] == '\0') || s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
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
			print_argument_error("unset: `", cmd_list->cmd[i]);
			i++;
			continue ;
		}
		j = 0;
		while (data->padloper_envp[j])
		{
			if(!unset_envcmp(data->padloper_envp[j], cmd_list->cmd[i]))
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
