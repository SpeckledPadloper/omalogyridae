/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_handling.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/04 14:31:48 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "../../libft/libft.h"
#include "hdr/executer.h"
#include "../hdr/structs.h"
#include <stdio.h>
#include "../signals/hdr/sigpadloper.h"
#include <readline/readline.h>

static char	*get_input(char *str)
{
	str = readline("> ");
	if (str == NULL)
		return (NULL);
	return (str);
}

static int	heredoc_handling(t_metadata *data, int *pipe_end, char *limiter)
{
	char	*str;
	char	*temp;
	int		here_status;

	str = NULL;
	pipe(pipe_end);
	data->heredocpid = fork();
	if (data->heredocpid == 0)
	{
		sig_setup(PROC_HDOC);
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
		if (str)
			free(str);
		close(pipe_end[1]);
		close(pipe_end[0]);
		exit(0);
	}
	close(pipe_end[1]);
	waitpid(data->heredocpid, &here_status, 0);
	if (WIFSIGNALED(here_status))
		data->exitstatus = 1;
	sig_setup(PROC_PARNT);
	if (data->exitstatus == 1)
		return (1);
	return (0);
}

int	get_all_heredoc(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int		i;
	int		ret;
	t_file	*head;

	i = 0;
	ret = 0;
	while (i < data->cmd_count)
	{
		cmd_list->heredoc_pipe[0] = 0;
		head = cmd_list->infile_list;
		while (cmd_list->infile_list)
		{
			if (cmd_list->infile_list->mode == RDIR_DOUBLE)
				ret = heredoc_handling
					(data, cmd_list->heredoc_pipe, cmd_list->infile_list->filename);
			if (cmd_list->infile_list->next && cmd_list->heredoc_pipe[0])
			{
				close_and_check(cmd_list->heredoc_pipe[0]);
				cmd_list->heredoc_pipe[0] = 0;
			}
			if (ret)
				return (1);
			cmd_list->infile_list = cmd_list->infile_list->next;
		}
		i++;
		cmd_list->infile_list = head;
		cmd_list = cmd_list->next;
	}
	return (0);
}
