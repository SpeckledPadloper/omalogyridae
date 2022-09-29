/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/29 11:37:51 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

void	check_echo(void)
{
	fprintf(stderr, "check echo\n");
	write(STDOUT_FILENO, "echo go to pipe\n", 16);
	exit(0);
}

void	check_export(void)
{
	fprintf(stderr, "check export\n");
	write(STDOUT_FILENO, "export go to pipe\n", 18);
	exit(0);
}


void	check_cd(void)
{
	fprintf(stderr, "check cd\n");
	exit(0);
}

void	check_pwd(void)
{
	fprintf(stderr, "check pwd\n");
	exit(0);
}

void	check_run_buildin(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int i;

	i = 0;
	while(i < BUILDIN_AMOUNT)
	{
		if (cmd_list->cmd[0] == data->buildins[i]) // strcmp!?
			data->fn_buildins[i]();
		i++;
	}
	return ;
}

void	execute_cmd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char	*path;

	path = NULL;
	open_necessary_infiles(data, cmd_list);
	open_necessary_outfiles(data, cmd_list);
	redirect_input(data, cmd_list); // cat | cat | ls
	redirect_output(data, cmd_list);
	close_unused_fd(data, cmd_list);
	check_run_buildin(data, cmd_list);
	path = path_builder(data, cmd_list->cmd[0]);
	execve(path, cmd_list->cmd, data->envp);
	print_error_exit("execve", errno, EXIT_FAILURE);
}

static void	fork_processes(t_metadata *data, t_exec_list_sim *cmd_list)
{
	if (data->cmd_count == 1)
		check_run_buildin(data, cmd_list);
	while (data->child_count < data->cmd_count)
	{
		data->fd_list->pipe_to_read = data->fd_list->pipe[0];
		if ((data->child_count + 1) != data->cmd_count)
		{
			if (pipe(data->fd_list->pipe) == -1)
				print_error_exit("pipe", errno, EXIT_FAILURE);
		}
		data->lastpid = fork();
		if (data->lastpid == -1)
			print_error_exit("fork", errno, EXIT_FAILURE);
		else if (data->lastpid == 0)
			execute_cmd(data, cmd_list);
		if ((data->child_count + 1) != data->cmd_count)
			close_and_check(data->fd_list->pipe[1]);
		if (data->fd_list->pipe_to_read != 0)
			close_and_check(data->fd_list->pipe_to_read);
		data->child_count++;
		if (cmd_list)
			cmd_list = cmd_list->next;
	}
}

void	executer(t_metadata *meta_data, t_exec_list_sim *cmd_list)
{
	int		status;
	pid_t	wp;

	get_all_heredoc(meta_data, cmd_list);
	if (!meta_data->cmd_count)
		return ; // no exit, this is parent, handle next promt
	/* er kan een node zijn zonder cmd, cat | < file | ls, dus data->cmd_count is geen goede case */
	fork_processes(meta_data, cmd_list);
	while (1)
	{
		wp = waitpid(-1, &status, 0);
		if (wp == meta_data->lastpid)
			meta_data->exitstatus = WEXITSTATUS(status);
		else if (wp == -1)
			break ;
	}
}