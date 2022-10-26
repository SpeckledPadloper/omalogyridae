/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/26 14:59:36 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/stat.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

char	*get_pwd(void)
{
	char	*pwd;
	char	*pwd_var;
	
	pwd = NULL;
	pwd = getcwd(pwd, sizeof(pwd));
	if (!pwd)
		print_error_exit("getcwd", errno, EXIT_FAILURE);
	pwd_var = ft_strjoin("PWD=", pwd);
	if (!pwd_var)
		print_error_exit("ft_strjoin", ENOMEM, EXIT_FAILURE);
	free(pwd);
	return (pwd_var);
}

char *get_oldpwd(char **swap)
{
	char *pwd_var;

	pwd_var = NULL;
	if (swap)
	{
		pwd_var = ft_strjoin("OLDPWD=", swap[1]);
		if (!pwd_var)
			print_error_exit("ft_strjoin", ENOMEM, EXIT_FAILURE);
	}
	else
	{
		pwd_var = ft_strdup("OLDPWD=");
		if (!pwd_var)
			print_error_exit("ft_strjoin", ENOMEM, EXIT_FAILURE);
	}
	return (pwd_var);
}

void	set_oldpwd(t_metadata *data, char *pwd_var)
{
	int pos;

	pos = has_var(data->padloper_envp, "OLDPWD");
	if (pos)
	{
		free(data->padloper_envp[pos]);
		add_env(data->padloper_envp, pwd_var, pos);
	}
}

bool	set_pwd_and_oldpwd(t_metadata *data, char *oldpwd)
{
	int pos;
	char *pwd_var;
	char **swap;

	swap = NULL;
	pos = has_var(data->padloper_envp, "PWD=");
	if (pos)
	{
		if (env_has_value(data->padloper_envp[pos]))
		{
			swap = ft_split(data->padloper_envp[pos], '=');
			if (!swap)
				print_error_exit("ft_split", ENOMEM, EXIT_FAILURE);
		}
		pwd_var = get_pwd();
		free(data->padloper_envp[pos]);
		add_env(data->padloper_envp, pwd_var, pos);
		free(pwd_var);
		pwd_var = get_oldpwd(swap);
		set_oldpwd(data, pwd_var);
		free(pwd_var);
		return (false);
	}
	set_oldpwd(data, "OLDPWD=");
	return (true);

}

void	create_oldpwd(char *oldpwd, t_metadata *data)
{
	char	*oldpwd_var;
	int 	pos;

	pos = has_var(data->padloper_envp, "OLDPWD");
	free(data->padloper_envp[pos]);
	oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
	if (!oldpwd_var)
		print_error_exit("ft_strjoin", ENOMEM, EXIT_FAILURE);
	add_env(data->padloper_envp, oldpwd_var, pos);
	free(oldpwd);
	free(oldpwd_var);
}

void	padloper_cd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char	*oldpwd;
	int		cur_pwd_unset;
	static bool prev_pwd_uset;

	oldpwd = NULL;
	if (!cmd_list->cmd[1])
	{
		builtin_error("cd: ", "missing arg", NO_PATH, data);
		return ;
	}
	oldpwd = getcwd(oldpwd, sizeof(oldpwd));
	if (!oldpwd)
		print_error_exit("getcwd", errno, EXIT_FAILURE);
	if (chdir(cmd_list->cmd[1]))
		builtin_error("cd: ", cmd_list->cmd[1], errno, data);
	data->env_updated = true;
	cur_pwd_unset = has_var(data->padloper_envp, "PWD=");
	if (prev_pwd_uset && !cur_pwd_unset)
		create_oldpwd(oldpwd, data);
	else
		prev_pwd_uset = set_pwd_and_oldpwd(data, oldpwd);
	return ;
}

/* 


	echo -nnnnn ! 
	_____________________________



 */
