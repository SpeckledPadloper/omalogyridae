/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/26 11:07:47 by lwiedijk      ########   odam.nl         */
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

	pwd = getcwd(pwd, sizeof(pwd));
	pos = has_var(data->padloper_envp, "PWD=");
	if (pos)
	{
		swap = ft_split(data->padloper_envp[pos], '=');
		pwd_var = ft_strjoin("PWD=", pwd);
		pos = has_var(data->padloper_envp, "PWD");
		if (pos)
		{
			free(data->padloper_envp[pos]);
			add_env(data->padloper_envp, pwd_var, pos);
		}
		free(pwd);
		free(pwd_var);
		pwd_var = ft_strjoin("OLDPWD=", swap[1]);
		pos = has_var(data->padloper_envp, "OLDPWD");
		free(data->padloper_envp[pos]);
		add_env(data->padloper_envp, pwd_var, pos);
		return (false);
	}
	pos = has_var(data->padloper_envp, "OLDPWD");
	free(data->padloper_envp[pos]);
	add_env(data->padloper_envp, "OLDPWD=", pos);
	return (true);

}

void	padloper_cd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char	*oldpwd;
	char	*oldpwd_var;
	int		cur_pwd_unset;
	int 	pos;
	static bool prev_pwd_uset;

	if (!cmd_list->cmd[1])
	{
		printf("minishell: cd: path as argument is required\n");
		return ;
	}
	oldpwd = getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(cmd_list->cmd[1]))
		builtin_error("cd: ", cmd_list->cmd[1], errno, data);
	cur_pwd_unset = has_var(data->padloper_envp, "PWD=");
	if (prev_pwd_uset && !cur_pwd_unset)
	{
		pos = has_var(data->padloper_envp, "OLDPWD");
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

	upon new shell, 

	oldpath is made empty!
	cd, set oldpath!

	cd update pwd in env!


	apropos tests:

	2>&1 redirect stderr to stdout
	2>out redirects stderr to a file named out

	
	!done bash sends "exit" by exit to stderr 


	!done echo! meerdere -n -n -n is 1 keer doen en de rest niet printen

	!done min max int bij exit status 

	export / unset with "invalid option", dus flag als eerste arg, 2 als exit code

	echo -nnnnn ! 
	_____________________________

	cd without arg, hoeven we niet, en wat als Home is unset en alles? gewoon not supported doen?


 */
