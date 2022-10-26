/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/26 13:57:52 by lwiedijk      ########   odam.nl         */
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

bool	set_pwd_and_oldpwd(t_metadata *data, char *oldpwd)
{
	int pos;
	char *pwd;
	char *pwd_var;
	char **swap;

	pwd = NULL;
	pwd = getcwd(pwd, sizeof(pwd));
	pos = has_var(data->padloper_envp, "PWD=");
	swap = NULL;
	if (pos)
	{
		if (env_has_value(data->padloper_envp[pos]))
			swap = ft_split(data->padloper_envp[pos], '=');
		pwd_var = ft_strjoin("PWD=", pwd);
		free(data->padloper_envp[pos]);
		add_env(data->padloper_envp, pwd_var, pos);
		free(pwd);
		free(pwd_var);
		if (swap)
			pwd_var = ft_strjoin("OLDPWD=", swap[1]);
		else
			pwd_var = ft_strdup("OLDPWD=");
		pos = has_var(data->padloper_envp, "OLDPWD");
		if (pos)
		{
			free(data->padloper_envp[pos]);
			add_env(data->padloper_envp, pwd_var, pos);
		}
		free(pwd_var);
		return (false);
	}
	pos = has_var(data->padloper_envp, "OLDPWD");
	if (pos)
	{
		free(data->padloper_envp[pos]);
		add_env(data->padloper_envp, "OLDPWD=", pos);
	}
	return (true);

}

void	padloper_cd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char	*oldpwd;
	char	*oldpwd_var;
	int		cur_pwd_unset;
	int 	pos;
	static bool prev_pwd_uset;

	oldpwd = NULL;
	if (!cmd_list->cmd[1])
	{
		printf("minishell: cd: path as argument is required\n");
		return ;
	}
	oldpwd = getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(cmd_list->cmd[1]))
		builtin_error("cd: ", cmd_list->cmd[1], errno, data);
	data->env_updated = true;
	cur_pwd_unset = has_var(data->padloper_envp, "PWD=");
	if (prev_pwd_uset && !cur_pwd_unset)
	{
		pos = has_var(data->padloper_envp, "OLDPWD");
		printf("pos = %d\n", pos);
		free(data->padloper_envp[pos]);
		oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
		add_env(data->padloper_envp, oldpwd_var, pos);
		free(oldpwd);
		free(oldpwd_var);
	}

	else
		prev_pwd_uset = set_pwd_and_oldpwd(data, oldpwd);
	return ;
}

/* 


	echo -nnnnn ! 
	_____________________________



 */
