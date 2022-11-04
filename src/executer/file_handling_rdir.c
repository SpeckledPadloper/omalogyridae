/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling_rdir.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/04 17:48:35 by mteerlin      ########   odam.nl         */
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

void	redirect_input(t_metadata *data, t_simple_cmd *cmd_list)
{
	if (data->cmd_count > 1 && data->child_count > 0)
	{
		if (dup2(data->fd_list->pipe_to_read, STDIN_FILENO) == -1)
			print_error_exit("dup2", errno, EXIT_FAILURE);
	}
	if (data->fd_list->fd_in)
	{
		if (dup2(data->fd_list->fd_in, STDIN_FILENO) == -1)
			print_error_exit("dup2", errno, EXIT_FAILURE);
	}
	if (cmd_list->heredoc_pipe[0])
	{
		if (dup2(cmd_list->heredoc_pipe[0], STDIN_FILENO) == -1)
			print_error_exit("dup2", errno, EXIT_FAILURE);
	}
}

void	redirect_output(t_metadata *data, t_simple_cmd *cmd_list)
{
	if (data->cmd_count > 1 && (data->child_count + 1) != data->cmd_count)
	{
		if (dup2(data->fd_list->pipe[1], STDOUT_FILENO) == -1)
			print_error_exit("dup2", errno, EXIT_FAILURE);
	}
	if (data->fd_list->fd_out)
	{
		if (dup2(data->fd_list->fd_out, STDOUT_FILENO) == -1)
			print_error_exit("dup2", errno, EXIT_FAILURE);
	}
}

void	close_unused_fd(t_metadata *data, t_simple_cmd *cmd_list)
{
	if (cmd_list->heredoc_pipe[0])
		close_and_check(cmd_list->heredoc_pipe[0]);
	if (data->fd_list->pipe[1] && (data->child_count + 1) != data->cmd_count)
		close_and_check(data->fd_list->pipe[1]);
	if (data->fd_list->pipe[0] && (data->child_count + 1) != data->cmd_count)
		close_and_check(data->fd_list->pipe[0]);
	if (data->fd_list->pipe_to_read)
		close_and_check(data->fd_list->pipe_to_read);
	if (data->fd_list->fd_in)
		close_and_check(data->fd_list->fd_in);
	if (data->fd_list->fd_out)
		close_and_check(data->fd_list->fd_out);
}
