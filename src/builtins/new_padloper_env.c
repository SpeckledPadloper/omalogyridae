/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_padloper_env.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/13 15:19:10 by lwiedijk      ########   odam.nl         */
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

void	populate_env(int envp_size, char **src, char **dst)
{
	int	i;
	int	size;

	i = 0;
	while (i < envp_size)
	{
		size = ft_strlen(src[i]);
		dst[i] = (char *)malloc(sizeof(char) * size + 1);
		if (!dst[i])
			print_error_exit("malloc", errno, EXIT_FAILURE);
		ft_strcpy(dst[i], src[i]);
		i++;
	}
	dst[i] = NULL;
}

char	**allocate_env(char **src, int *envp_size, int remove, int add)
{
	char	**dst;
	int		i;

	dst = NULL;
	i = 0;
	while (src[i])
		i++;
	i += add;
	i -= remove;
	dst = (char **)malloc(sizeof(char *) * i + 1);
	if (!dst)
		print_error_exit("malloc", errno, EXIT_FAILURE);
	*envp_size = i;
	return (dst);
}

void	increment_shlvl(char **new_padloper_envp)
{
	int		res;
	char	*res_str;
	int		i;

	i = 0;
	while (new_padloper_envp[i])
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

char	**new_padloper_envp(char **original_envp, int *envp_size)
{
	char	**new_padloper_envp;
	int		missing_var;

	missing_var = 0;
	if (!has_var(original_envp, "SHLVL="))
		missing_var++;
	if (!has_var(original_envp, "PWD="))
		missing_var++;
	new_padloper_envp = allocate_env
		(original_envp, envp_size, false, missing_var);
	populate_env(*envp_size - missing_var, original_envp, new_padloper_envp);
	if (!has_var(new_padloper_envp, "PWD="))
		set_pwd(new_padloper_envp, ((*envp_size) - missing_var));
	if (has_var(new_padloper_envp, "SHLVL="))
		increment_shlvl(new_padloper_envp);
	else
		add_env(new_padloper_envp, "SHLVL=1", ((*envp_size) - 1));
	new_padloper_envp[*envp_size] = NULL;
	return (new_padloper_envp);
}
