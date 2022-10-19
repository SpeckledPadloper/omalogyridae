/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_padloper_env.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/19 15:54:41 by lwiedijk      ########   odam.nl         */
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

void	populate_env(int envp_size, char **src, char **dst, int *data_envp_size)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	while (j < envp_size)
	{
		if (!env_has_value(src[j]))
		{
			printf("size befor populate envvalue %d -> %s\n", *data_envp_size, src[j]);
			(*data_envp_size)--;
			printf("size after populate envvalue %d -> %s\n", *data_envp_size, src[j]);
			j++;
			continue;
		}
		size = ft_strlen(src[j]);
		dst[i] = (char *)malloc(sizeof(char) * size + 1);
		if (!dst[i])
			print_error_exit("malloc", errno, EXIT_FAILURE);
		ft_strcpy(dst[i], src[j]);
		i++;
		j++;
	}
	dst[i] = NULL;
}

char	**allocate_env(char **src, t_metadata *data, int add)
{
	char	**dst;
	int		env_buffer;
	int		i;

	dst = NULL;
	env_buffer = 0;
	if (add)
		env_buffer = 3;
	i = 0;
	while (src[i])
		i++;
	i += add;
	dst = (char **)malloc(sizeof(char *) * i + env_buffer + 1);
	if (!dst)
		print_error_exit("malloc", errno, EXIT_FAILURE);
	data->envp_size = i;
	if (add)
		data->envp_space = i + env_buffer;
	printf("in allocate: size = %d, i = %d, space = %d, envbuf = %d, add = %d\n", data->envp_size, i, data->envp_space, env_buffer, add);
	return (dst);
}

void	increment_shlvl(char **new_padloper_envp)
{
	int		res;
	char	*res_str;
	int		i;

	i = has_var(new_padloper_envp, "SHLVL=");
	res = ft_atoi(&new_padloper_envp[i][6]);
	res++;
	res_str = ft_itoa(res);
	free(new_padloper_envp[i]);
	new_padloper_envp[i] = ft_strjoin("SHLVL=", res_str);
	free(res_str);
}

void	reset_oldpwd(char **new_padloper_envp, int pos)
{
	int i;

	i = 0;
	i = has_var(new_padloper_envp, "OLDPWD=");
	if (i)
	{
		free(new_padloper_envp[i]);
		add_env(new_padloper_envp, "OLDPWD", i);
	}
	else
		add_env(new_padloper_envp, "OLDPWD", pos);
}

void	set_pwd(char **new_padloper_envp, int pos)
{
	char	*buf;
	char	*pwd_var;

	buf = NULL;
	buf = getcwd(buf, sizeof(buf));
	if (!buf)
		print_error_exit("getcwd", errno, EXIT_FAILURE);
	pwd_var = ft_strjoin("PWD=", buf);
	add_env(new_padloper_envp, pwd_var, pos);
	free(buf);
	free(pwd_var);
}

char	**new_padloper_envp(char **original_envp, t_metadata *data, int *envp_size)
{
	char	**new_padloper_envp;
	int		missing_var;

	missing_var = 0;
	if (!has_var(original_envp, "SHLVL="))
		missing_var++;
	if (!has_var(original_envp, "PWD="))
		missing_var++;
	if (!has_var(original_envp, "OLDPWD="))
		missing_var++;
	printf("missing var is %d\n", missing_var);
	new_padloper_envp = allocate_env
		(original_envp, data, missing_var);
	printf("size befor populate %d\n", *envp_size);
	populate_env(*envp_size - missing_var, original_envp, new_padloper_envp, envp_size);
	printf("size after populate %d\n", *envp_size);
	reset_oldpwd(new_padloper_envp, (*envp_size - missing_var));
	if (!has_var(new_padloper_envp, "PWD="))
		set_pwd(new_padloper_envp, ((*envp_size) - (missing_var - (missing_var == 3))));
	if (has_var(new_padloper_envp, "SHLVL="))
		increment_shlvl(new_padloper_envp);
	else
		add_env(new_padloper_envp, "SHLVL=1", ((*envp_size) - 1));
	new_padloper_envp[*envp_size] = NULL;
	return (new_padloper_envp);
}
	