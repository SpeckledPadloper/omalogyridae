/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/01 16:27:42 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../libft/libft.h"
#include "../executer/executer.h"

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

char **new_padloper_envp(char **original_envp)
{
	char **new_padloper_envp;
	//int i;

	new_padloper_envp = copy_env(original_envp);
	//i = 0;
	//while(new_padloper_envp[i])
	//{
	//	if (!ft_strncmp(new_padloper_envp[i], "SHLVL=", 6))
	//	{
	//		
	//	}
	//	i++;
	//}

	//int i;
	//i = 0;
	//while(new_padloper_envp[i])
	//{
	//	printf("new: %s\n", new_padloper_envp[i]);
	//	i++;
	//}
	return (new_padloper_envp);
}

void	padloper_env(t_metadata *data)
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
