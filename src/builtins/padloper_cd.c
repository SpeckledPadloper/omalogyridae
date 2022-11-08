/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/04 17:46:49 by mteerlin      ########   odam.nl         */
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

void	padloper_cd(t_metadata *data, t_simple_cmd *cmd_list)
{
	char		*oldpwd;
	int			cur_pwd_unset;
	static bool	prev_pwd_uset;

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
