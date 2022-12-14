/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_builder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/10 14:38:08 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <errno.h>

bool	is_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

static char	*build_path(char *cmd, char **env_path, int count)
{
	char	*path;
	int		i;
	int		is_not_executable;

	path = NULL;
	i = 0;
	while (i < count)
	{
		path = ft_strjoin("/", cmd);
		if (!path)
			print_error_exit("ft_strjoin", ENOMEM, EXIT_FAILURE);
		path = ft_strjoin(env_path[i], path);
		if (!path)
			print_error_exit("ft_strjoin", ENOMEM, EXIT_FAILURE);
		is_not_executable = access(path, F_OK | X_OK);
		if (is_not_executable)
		{
			free(path);
			path = NULL;
		}
		else
			break ;
		i++;
	}
	return (path);
}

static char	**get_env_path_array(char **envp, int *count)
{
	char	**env_path;
	char	**temp;
	int		i;

	i = 0;
	temp = NULL;
	env_path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			temp = ft_split(envp[i], '=');
			if (!temp)
				print_error_exit("ft_split", ENOMEM, EXIT_FAILURE);
			env_path = ft_split_and_count(temp[1], ':', count);
			if (!env_path)
				print_error_exit("ft_split", ENOMEM, EXIT_FAILURE);
			free_2d_array(temp);
			break ;
		}
		i++;
	}
	return (env_path);
}

static char	*check_absolute_path(char *path)
{
	int			is_not_executable;
	int			file_does_not_exist;
	struct stat	check_dir;

	if (!ft_strcmp(path, ""))
		print_error_exit(path, CNF, CMD_NOT_FOUND);
	if (!is_path(path))
		return (NULL);
	stat(path, &check_dir);
	if (S_ISDIR(check_dir.st_mode))
		print_error_exit(path, IS_DIR, CMD_CANT_EXE);
	is_not_executable = access(path, F_OK | X_OK);
	if (is_not_executable)
	{
		file_does_not_exist = access(path, F_OK);
		if (file_does_not_exist)
			print_error_exit(path, errno, CMD_NOT_FOUND);
		else
			print_error_exit(path, errno, CMD_CANT_EXE);
	}
	return (path);
}

char	*path_builder(t_metadata *data, char *cmd)
{
	char	*path;
	char	**env_path;
	int		count;

	count = 0;
	path = NULL;
	path = check_absolute_path(cmd);
	if (!path)
	{
		env_path = get_env_path_array(data->padloper_envp, &count);
		if (env_path == NULL)
			print_error_exit(cmd, ERRNO_NO_SUCH_FILE, CMD_NOT_FOUND);
		path = build_path(cmd, env_path, count);
		free_2d_array(env_path);
	}
	if (!path)
		print_error_exit(cmd, CNF, CMD_NOT_FOUND);
	return (path);
}
