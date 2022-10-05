/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/05 11:37:13 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../libft/libft.h"
#include "../executer/executer.h"

// protect all below malloc calls! 

char **allocate_env(char **src, int *envp_size, int unset, int export)
{
	char **dst;
	int i;
	int j;

	dst = NULL;
	i = 0;
	while(src[i])
		i++;
	i += export;
	i -= unset;
	dst = (char**)malloc(sizeof(char*) * i + 1);
	*envp_size = i;
	i = 0;
	while(src[i])
	{
		j = 0;
		while(src[i][j])
			j++;
		dst[i] = (char*)malloc(sizeof(char) * j + 1);
		ft_strcpy(dst[i], src[i]);
		i++;	
	}
	dst[i] = NULL;
	return (dst);
}

char **new_padloper_envp(char **original_envp, int *envp_size)
{
	char **new_padloper_envp;
	int i;
	int res;
	char *res_str;

	new_padloper_envp = allocate_env(original_envp, envp_size, false, false);
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
		// handle SHLVL not set, handle PWD not set;
		i++;
	}
	//*envp_size = i; 
	return (new_padloper_envp);
}

void	padloper_env(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int i;

	i = 0;
	while(data->padloper_envp[i])
	{
		printf("padloper realness: %s\n", data->padloper_envp[i]);
		i++;
	}
	exit(0);
}
