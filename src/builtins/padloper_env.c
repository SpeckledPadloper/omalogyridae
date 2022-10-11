/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/11 11:47:14 by lwiedijk      ########   odam.nl         */
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

void populate_env(int envp_size, char **src, char **dst)
{
	int i;
	int size;
	
	i = 0;
	while(i < envp_size)
	{
		size = ft_strlen(src[i]);
		dst[i] = (char*)malloc(sizeof(char) * size + 1);
		if (!dst[i])
			print_error_exit("malloc", errno, EXIT_FAILURE);
		ft_strcpy(dst[i], src[i]);
		i++;	
	}
	dst[i] = NULL;
}

void	env_pointer_cpy(int envp_size, char **old, char **new)
{
	int i;

	i = 0;
	while(i < envp_size)
	{
		new[i] = old[i];
		i++;
	}
	new[envp_size] = NULL;
}

void add_env(char **padloper_env, char *var, int pos)
{
	int size;

	size = ft_strlen(var);
	padloper_env[pos] = (char *)malloc(sizeof(char) * size + 1);
	if (!padloper_env[pos])
			print_error_exit("malloc", errno, EXIT_FAILURE);
	ft_strcpy(padloper_env[pos], var);
	padloper_env[pos + 1] = NULL;
}

char **allocate_env(char **src, int *envp_size, int remove, int add)
{
	char **dst;
	int i;

	dst = NULL;
	i = 0;
	while(src[i])
		i++;
	i += add;
	i -= remove;
	dst = (char**)malloc(sizeof(char*) * i + 1);
	if (!dst)
		print_error_exit("malloc", errno, EXIT_FAILURE);
	*envp_size = i;
	return (dst);
}

bool	has_var(char **array, char *var)
{
	int i;

	i = 0;
	while(array[i])
	{
		if (!envcmp(array[i], var))
			return(true);
		i++;
	}
	return(false);
}

void	increment_shlvl(char **new_padloper_envp)
{
	int		res;
	char	*res_str;
	int		i;

	i = 0;
	while(new_padloper_envp[i])
	{
		if (!envcmp(new_padloper_envp[i], "SHLVL="))
		{
			res = ft_atoi(&new_padloper_envp[i][6]);
			res++;
			res_str = ft_itoa(res);
			free(new_padloper_envp[i]);
			new_padloper_envp[i] = ft_strjoin("SHLVL=", res_str);
			free(res_str);
		}
		i++;
	}
}

char **new_padloper_envp(char **original_envp, int *envp_size)
{
	char **new_padloper_envp;
	int missing_var;

	missing_var = 0;
	if (!has_var(original_envp, "SHLVL="))
		missing_var++;
	if (!has_var(original_envp, "PWD="))
		missing_var++;
	new_padloper_envp = allocate_env(original_envp, envp_size, false, missing_var);
	populate_env(*envp_size - missing_var, original_envp, new_padloper_envp);
	if (!has_var(new_padloper_envp, "PWD="))
		add_env(new_padloper_envp, "PWD=doeditnog!", ((*envp_size) - missing_var));
	if (has_var(new_padloper_envp, "SHLVL="))
		increment_shlvl(new_padloper_envp);
	else
		add_env(new_padloper_envp, "SHLVL=1", ((*envp_size) - 1));
	new_padloper_envp[*envp_size] = NULL;
	return (new_padloper_envp);
}

void	padloper_env(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int i;

	if (!data || !data->padloper_envp)
		print_error_exit("padloper_env", EMPTY, EXIT_FAILURE);
	i = 0;
	while(data->padloper_envp[i])
	{
		printf("padlopers env: %s\n", data->padloper_envp[i]);
		i++;
	}
	return ;
}
