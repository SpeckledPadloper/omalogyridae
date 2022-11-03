/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_handling.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/03 15:09:59 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "../../libft/libft.h"
#include "hdr/executer.h"
#include "../hdr/structs.h"
#include <stdio.h>

static char	*get_input(char *str)
{
	int ret;

	ret = 0;
	write (STDOUT_FILENO, "> ", 2);
	ret = get_next_line(STDIN_FILENO, &str);
	if (ret == 0)
		return (NULL);
	if (ret == -1)
		print_error_exit("malloc", errno, EXIT_FAILURE);
	return (str);
}

static void	heredoc_handling(int *pipe_end, char *limiter)
{
	char	*str;
	char	*temp;

	str = NULL;
	pipe(pipe_end);
	str = get_input(str);
	while (str && ft_strcmp(limiter, str))
	{
		temp = ft_strjoin(str, "\n");
		if (!temp)
			print_error_exit("malloc", errno, EXIT_FAILURE);
		write (pipe_end[1], temp, ft_strlen(temp));
		free(str);
		free(temp);
		str = get_input(str);
	}
	free(str);
	close(pipe_end[1]);
}

void	get_all_heredoc(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int		i;
	t_file	*head;

	i = 0;
	while (i < data->cmd_count)
	{
		cmd_list->heredoc_pipe[0] = 0;
		head = cmd_list->infile_list;
		while (cmd_list->infile_list)
		{
			if (cmd_list->infile_list->mode == RDIR_DOUBLE)
				heredoc_handling
					(cmd_list->heredoc_pipe, cmd_list->infile_list->filename);
			if (cmd_list->infile_list->next && cmd_list->heredoc_pipe[0])
			{
				close_and_check(cmd_list->heredoc_pipe[0]);
				cmd_list->heredoc_pipe[0] = 0;
			}
			cmd_list->infile_list = cmd_list->infile_list->next;
		}
		i++;
		cmd_list->infile_list = head;
		cmd_list = cmd_list->next;
	}
}
