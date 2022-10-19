/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/19 09:43:58 by lwiedijk      ########   odam.nl         */
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

//bool	check_arg(t_metadata *data, char *path)
//{
//	struct stat check;
//	int file_does_not_exist;
//
//	file_does_not_exist = access(path, F_OK);
//	if (file_does_not_exist)
//	{
//		builtin_error("cd: ", path, errno, data);
//		return (false);
//	}
//	stat(path, &check);
//	if (!S_ISDIR(check.st_mode))
//	{
//		builtin_error("cd: ", path, NOT_DIR, data);
//		return (false);
//	}
//	return (true);
//}

void	padloper_cd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	if (!cmd_list->cmd[1])
	{
		printf("minishell: cd: path as argument is required\n");
		return ;
	}
	//if (check_arg(data, cmd_list->cmd[1]))
		if (chdir(cmd_list->cmd[1]))
			builtin_error("cd: ", cmd_list->cmd[1], errno, data);
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
	_____________________________

	cd without arg, hoeven we niet, en wat als Home is unset en alles? gewoon not supported doen?


 */
