/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/26 21:18:27 by mteerlin      ########   odam.nl         */
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

static void	interrupt_handler(int sig)
{
	int	status;

	status = 0;
	write(1, "signal found in child\n", 23);
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", 1);
		ft_putnbr_fd(sig, 1);
		ft_putchar_fd('\n', 1);
	}
}

bool	check_run_buildin(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int i;

	i = 0;
	if (!(cmd_list->cmd))
		return false;
	while(i < BUILDIN_AMOUNT)
	{
		if (!(ft_strcmp(cmd_list->cmd[0], data->buildins[i])))
		{
			data->fn_buildins[i](data, cmd_list);
			return true;
		}
		i++;
	}
	return false;
}

void	execute_cmd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char	*path;
	int		status;

	path = NULL;
	status = 0;
	signal(SIGQUIT, &interrupt_handler);
	printf("%d\n", WTERMSIG(status));
	if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
		exit(128 + WTERMSIG(status));
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

static void	fork_processes(t_metadata *data, t_exec_list_sim *cmd_list)
{
	if (data->cmd_count == 1 && cmd_list->cmd)
		if (check_run_buildin(data, cmd_list))
			return ;
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

	status = 0;
	meta_data->cmd_count = ft_sim_lstsize(cmd_list);
	get_all_heredoc(meta_data, cmd_list);
	if (!meta_data->cmd_count)
		return ;
	fork_processes(meta_data, cmd_list);
	while (1)
	{
		wp = waitpid(-1, &status, 0);
		// fprintf(stderr, "wp signal terminated?? [%d] with: [%d] exitstat [%d] \n", WIFSIGNALED(status), WTERMSIG(status), WEXITSTATUS(status));
		if (WIFSIGNALED(status))
		{
			meta_data->exitstatus = 128 + WTERMSIG(status);
			break ;
		}
		if (wp == meta_data->lastpid)
			meta_data->exitstatus = WEXITSTATUS(status);
		else if (wp == -1)
			break ;
	}
}
