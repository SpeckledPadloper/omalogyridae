/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling_builtin.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/10 14:31:25 by lwiedijk      ########   odam.nl         */
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

void	open_necessary_infiles_bi(t_metadata *data, t_simple_cmd *cmd_list)

{	
	while (cmd_list->infile_list)
	{
		if (cmd_list->infile_list->mode == RDIR_AMBIGUOUS)
			builtin_error
				("", cmd_list->infile_list->filename, AR, data);
		if (cmd_list->infile_list->mode == RDIR_SINGLE)
		{
			data->fd_list->fd_in = open
				(cmd_list->infile_list->filename, O_RDONLY);
			if (data->fd_list->fd_in < 0)
			{
				builtin_error
					("", cmd_list->infile_list->filename, errno, data);
				data->fd_list->fd_in = 0;
			}
		}
		if (cmd_list->infile_list->next && data->fd_list->fd_in)
		{
			close_and_check(data->fd_list->fd_in);
			data->fd_list->fd_in = 0;
		}
		cmd_list->infile_list = cmd_list->infile_list->next;
	}
}

void	open_and_check_file_bi(t_metadata *data, t_simple_cmd *cmd_list)
{
	if (cmd_list->outfile_list->mode == RDIR_SINGLE)
	{
		data->fd_list->fd_out = open(cmd_list->outfile_list->filename,
				O_CREAT | O_WRONLY | O_TRUNC, MODE_RW_R_R);
		if (data->fd_list->fd_out < 0)
		{
			builtin_error
				("", cmd_list->outfile_list->filename, errno, data);
			data->fd_list->fd_out = 0;
		}
	}
	if (cmd_list->outfile_list->mode == RDIR_DOUBLE)
	{
		data->fd_list->fd_out = open(cmd_list->outfile_list->filename,
				O_CREAT | O_WRONLY | O_APPEND, MODE_RW_R_R);
		if (data->fd_list->fd_out < 0)
		{
			builtin_error
				("", cmd_list->outfile_list->filename, errno, data);
			data->fd_list->fd_out = 0;
		}
	}
}

void	open_necessary_outfiles_bi(t_metadata *data, t_simple_cmd *cmd_list)
{
	while (cmd_list->outfile_list)
	{
		if (cmd_list->outfile_list->mode == RDIR_AMBIGUOUS)
			builtin_error
				("", cmd_list->outfile_list->filename, AR, data);
		open_and_check_file_bi(data, cmd_list);
		if (cmd_list->outfile_list->next && data->fd_list->fd_out)
		{
			close_and_check(data->fd_list->fd_out);
			data->fd_list->fd_out = 0;
		}
		cmd_list->outfile_list = cmd_list->outfile_list->next;
	}
}

void	redirect_output_bi(t_metadata *data)
{
	if (data->fd_list->fd_out)
	{
		if (dup2(data->fd_list->fd_out, STDOUT_FILENO) == -1)
			print_error_exit("dup2", errno, EXIT_FAILURE);
	}
}

void	close_unused_fd_bi(t_metadata *data, t_simple_cmd *cmd_list)
{
	if (cmd_list->heredoc_pipe[0])
		close_and_check(cmd_list->heredoc_pipe[0]);
	if (data->fd_list->fd_in)
		close_and_check(data->fd_list->fd_in);
	if (data->fd_list->fd_out)
		close_and_check(data->fd_list->fd_out);
}
