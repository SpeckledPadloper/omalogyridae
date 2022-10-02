/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/02 13:21:58 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../libft/libft.h"
#include "../executer/executer.h"

// protect all below malloc calls! 

char **copy_env(char **src)
{
	char **dst;
	int i;
	int j;

	dst = NULL;
	i = 0;
	while(src[i])
		i++;
	dst = (char**)malloc(sizeof(char*) * i + 1);
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

	new_padloper_envp = copy_env(original_envp);
	i = 0;
	while(new_padloper_envp[i])
	{
		if (!ft_strncmp(new_padloper_envp[i], "SHLVL=", 6))
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
	*envp_size = i; 
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
