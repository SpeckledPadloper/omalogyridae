/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/08 13:24:43 by lwiedijk      ########   odam.nl         */
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
#include <errno.h>
#include <signal.h>
#include "../signals/hdr/sigpadloper.h"

void	do_parent_redirect(t_metadata *data, t_simple_cmd *cmd_list)
{
	open_necessary_infiles_bi(data, cmd_list);
	open_necessary_outfiles_bi(data, cmd_list);
	redirect_output_bi(data, cmd_list);
	close_unused_fd_bi(data, cmd_list);
}

bool	check_run_buildin(t_metadata *data, t_simple_cmd *cmd_list)
{
	int	i;
	int	reset_stdout;

	i = 0;
	reset_stdout = dup(STDOUT_FILENO);
	if (reset_stdout == -1)
		print_error_exit("dup", errno, EXIT_FAILURE);
	if (!(cmd_list->cmd))
		return (false);
	while (i < NR_BLDINS)
	{
		if (!(ft_strcmp(cmd_list->cmd[0], data->buildins[i])))
		{
			if (data->cmd_count == 1)
				do_parent_redirect(data, cmd_list);
			if (data->exitstatus == EXIT_SUCCESS)
				data->fn_buildins[i](data, cmd_list);
			if (dup2(reset_stdout, STDOUT_FILENO) == -1)
				print_error_exit("dup2", errno, EXIT_FAILURE);
			close_and_check(reset_stdout);
			return (true);
		}
		i++;
	}
	return (false);
}

void	execute_cmd(t_metadata *data, t_simple_cmd *cmd_list)
{
	char	*path;
	int		status;

	path = NULL;
	status = 0;
	sig_setup(PROC_CHLD);
	open_necessary_infiles(data, cmd_list);
	open_necessary_outfiles(data, cmd_list);
	redirect_input(data, cmd_list);
	redirect_output(data, cmd_list);
	close_unused_fd(data, cmd_list);
	if (!(cmd_list->cmd))
		exit(EXIT_SUCCESS);
	if (check_run_buildin(data, cmd_list))
		exit(data->exitstatus);
	path = path_builder(data, cmd_list->cmd[0]);
	execve(path, cmd_list->cmd, data->padloper_envp);
	print_error_exit("execve", errno, EXIT_FAILURE);
}

static bool	fork_processes(t_metadata *data, t_simple_cmd *cmd_list)
{
	if (data->cmd_count == 1 && cmd_list->cmd)
		if (check_run_buildin(data, cmd_list))
			return (false);
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
	return (true);
}

void	executer(t_metadata *meta_data, t_simple_cmd *cmd_list)
{
	int		status;
	pid_t	wp;

	status = 0;
	meta_data->cmd_count = ft_sim_lstsize(cmd_list);
	if (get_all_heredoc(meta_data, cmd_list))
		return ;
	if (!meta_data->cmd_count)
		return ;
	if (!fork_processes(meta_data, cmd_list))
		return ;
	signal(SIGINT, SIG_IGN);
	change_tcattr(PROC_PARNT);
	waitpid(meta_data->lastpid, &status, 0);
	while (1)
	{
		wp = waitpid(-1, 0, 0);
		if (wp == -1)
			break ;
	}
	if (!WIFSIGNALED(status))
		meta_data->exitstatus = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		meta_data->exitstatus = sig_exit(status);
	sig_setup(PROC_PARNT);
}
