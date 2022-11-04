/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_handling_open.c                               :+:    :+:            */
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

void	open_necessary_infiles(t_metadata *data, t_simple_cmd *cmd_list)

{	
	while (cmd_list->infile_list)
	{
		if (cmd_list->infile_list->mode == RDIR_AMBIGUOUS)
			print_error_exit
				(cmd_list->infile_list->filename, AR, EXIT_FAILURE);
		if (cmd_list->infile_list->mode == RDIR_SINGLE)
		{
			data->fd_list->fd_in = open
				(cmd_list->infile_list->filename, O_RDONLY);
			if (data->fd_list->fd_in < 0)
				print_error_exit
					(cmd_list->infile_list->filename, errno, EXIT_FAILURE);
		}
		if (cmd_list->infile_list->next && data->fd_list->fd_in)
		{
			close_and_check(data->fd_list->fd_in);
			data->fd_list->fd_in = 0;
		}
		cmd_list->infile_list = cmd_list->infile_list->next;
	}
}

void	open_and_check_file(t_metadata *data, t_simple_cmd *cmd_list)
{
	if (cmd_list->outfile_list->mode == RDIR_SINGLE)
	{
		data->fd_list->fd_out = open(cmd_list->outfile_list->filename,
				O_CREAT | O_WRONLY | O_TRUNC, MODE_RW_R_R);
		if (data->fd_list->fd_out < 0)
			print_error_exit
				(cmd_list->outfile_list->filename, errno, EXIT_FAILURE);
	}
	if (cmd_list->outfile_list->mode == RDIR_DOUBLE)
	{
		data->fd_list->fd_out = open(cmd_list->outfile_list->filename,
				O_CREAT | O_WRONLY | O_APPEND, MODE_RW_R_R);
		if (data->fd_list->fd_out < 0)
			print_error_exit
				(cmd_list->outfile_list->filename, errno, EXIT_FAILURE);
	}
}

void	open_necessary_outfiles(t_metadata *data, t_simple_cmd *cmd_list)
{
	while (cmd_list->outfile_list)
	{
		if (cmd_list->outfile_list->mode == RDIR_AMBIGUOUS)
			print_error_exit
				(cmd_list->outfile_list->filename, AR, EXIT_FAILURE);
		open_and_check_file(data, cmd_list);
		if (cmd_list->outfile_list->next && data->fd_list->fd_out)
		{
			close_and_check(data->fd_list->fd_out);
			data->fd_list->fd_out = 0;
		}
		cmd_list->outfile_list = cmd_list->outfile_list->next;
	}
}
