/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/08 09:33:45 by lwiedijk      ########   odam.nl         */
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

char	*export_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	dest[i] = '"';
	while (src[i] != '\0')
	{
		dest[i + 1] = src[i];
		i++;
	}
	dest[i + 1] = '"';
	dest[i + 2] = '\0';
	return (dest);
}

void populate_export(int size, char **src, char **dst)
{
	int i;
	int j;
	
	i = 0;
	while(i < size)
	{
		j = 0;
		while(src[i][j])
			j++;
		dst[i] = (char*)malloc(sizeof(char) * j + 3);
		if (!dst)
			print_error_exit("malloc", errno, EXIT_FAILURE);
		export_strcpy(dst[i], src[i]);
		i++;	
	}
	dst[i] = NULL;
}

void populate_env(int size, char **src, char **dst)
{
	int i;
	int j;
	
	i = 0;
	while(i < size)
	{
		j = 0;
		while(src[i][j])
			j++;
		dst[i] = (char*)malloc(sizeof(char) * j + 1);
		if (!dst)
			print_error_exit("malloc", errno, EXIT_FAILURE);
		ft_strcpy(dst[i], src[i]);
		i++;	
	}
	dst[i] = NULL;
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
	populate_env(*envp_size, src, dst);
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

	if (!data->padloper_envp || !cmd_list)
	{
		fprintf(stderr, "Parameters are NULL");
		print_error_exit("padloper_env", EMPTY, EXIT_FAILURE);
	}
	i = 0;
	while(data->padloper_envp[i])
	{
		printf("padloper realness: %s\n", data->padloper_envp[i]);
		i++;
	}
	return ;
}
