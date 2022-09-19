/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/19 15:58:20 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

void	open_necessary_infiles(t_metadata *data, t_exec_list_sim *cmd_list)

{
	while (cmd_list->infile_list)
	{
		if (cmd_list->infile_list->mode == LESS)
		{
			data->fd_list->fd_in = open(cmd_list->infile_list->filename, O_RDONLY);
			if (data->fd_list->fd_in < 0)
				print_error_exit(cmd_list->infile_list->filename, errno, EXIT_FAILURE);
		}
		if (cmd_list->infile_list->next && data->fd_list->fd_in)
		{
			close_and_check(data->fd_list->fd_in);
			data->fd_list->fd_in = 0;
		}
		cmd_list->infile_list = cmd_list->infile_list->next;
	}
}

void	open_necessary_outfiles(t_metadata *data, t_exec_list_sim *cmd_list)
{
	while (cmd_list->outfile_list)
	{
		if (cmd_list->outfile_list->mode == GREAT)
		{
			data->fd_list->fd_out = open(cmd_list->outfile_list->filename, O_CREAT | O_WRONLY | O_TRUNC, MODE_RW_R_R);
			if (data->fd_list->fd_out < 0)
				print_error_exit(cmd_list->outfile_list->filename, errno, EXIT_FAILURE);
		}
		if (cmd_list->outfile_list->mode == GREATGREAT)
		{
			data->fd_list->fd_out = open(cmd_list->outfile_list->filename, O_CREAT | O_WRONLY | O_APPEND, MODE_RW_R_R);
			if (data->fd_list->fd_out < 0)
				print_error_exit(cmd_list->outfile_list->filename, errno, EXIT_FAILURE);
		}
		if (cmd_list->outfile_list->next && data->fd_list->fd_out)
		{
			close_and_check(data->fd_list->fd_out);
			data->fd_list->fd_out = 0;
		}
		cmd_list->outfile_list = cmd_list->outfile_list->next;
	}
}

void	redirect_input(t_metadata *data, t_exec_list_sim *cmd_list)
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

void	redirect_output(t_metadata *data, t_exec_list_sim *cmd_list)
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

void	close_unused_fd(t_metadata *data, t_exec_list_sim *cmd_list)
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
