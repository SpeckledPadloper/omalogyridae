/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/08 20:03:23 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

void	add_env(char **padloper_env, char *var, int pos)
{
	int	size;

	size = ft_strlen(var);
	padloper_env[pos] = (char *)malloc(sizeof(char) * (size + 1));
	if (!padloper_env[pos])
		print_error_exit("malloc", errno, EXIT_FAILURE);
	ft_strcpy(padloper_env[pos], var);
}

bool	env_has_value(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	envcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (!(s1[i] == '=' || s1[i] == '\0') || !(s2[i] == '=' || s2[i] == '\0'))
	{
		if (s1[i] == s2[i])
			i++;
		else if (s1[i] == '=')
			return (0 - s2[i]);
		else if (s2[i] == '=')
			return (s1[i] - 0);
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

int	has_var(char **array, char *var)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!envcmp(array[i], var))
			return (i);
		i++;
	}
	return (0);
}

char	**allocate_env(char **src, t_metadata *data, int add)
{
	char	**dst;
	int		env_buffer;
	int		i;

	dst = NULL;
	env_buffer = 0;
	if (add)
		env_buffer = 10;
	i = 0;
	while (src[i])
		i++;
	i += add;
	dst = (char **)malloc(sizeof(char *) * (i + env_buffer + 1));
	if (!dst)
		print_error_exit("malloc", errno, EXIT_FAILURE);
	data->envp_size = i;
	if (add)
		data->envp_space = i + env_buffer;
	return (dst);
}
