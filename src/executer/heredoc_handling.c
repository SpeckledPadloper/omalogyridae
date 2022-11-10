/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_handling.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/10 14:36:09 by lwiedijk      ########   odam.nl         */
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

static void	do_heredoc(int *pipe_end, char *limiter)
{
	char	*str;
	char	*temp;

	str = NULL;
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

static int	heredoc_handling(t_metadata *data, int *pipe_end, char *limiter)
{
	int		here_status;

	pipe(pipe_end);
	data->heredocpid = fork();
	if (data->heredocpid == 0)
		do_heredoc(pipe_end, limiter);
	signal(SIGINT, SIG_IGN);
	change_tcattr(PROC_PARNT);
	close(pipe_end[1]);
	waitpid(data->heredocpid, &here_status, 0);
	if (WIFSIGNALED(here_status))
	{
		data->exitstatus = 1;
		write(1, "\n", 1);
	}
	sig_setup(PROC_PARNT);
	if (data->exitstatus == 1)
		return (1);
	return (0);
}

int	get_heredocs_this_cmd(t_metadata *data, t_simple_cmd *cmd_list)
{
	t_file	*itter;
	int		ret;

	ret = 0;
	cmd_list->heredoc_pipe[0] = 0;
	itter = cmd_list->infile_list;
	while (itter)
	{
		if (itter->mode == RDIR_DOUBLE)
			ret = heredoc_handling(data, cmd_list->heredoc_pipe,
					itter->filename);
		if (ret)
		{
			close_and_check(cmd_list->heredoc_pipe[0]);
			return (1);
		}
		if (itter->next && cmd_list->heredoc_pipe[0])
		{
			close_and_check(cmd_list->heredoc_pipe[0]);
			cmd_list->heredoc_pipe[0] = 0;
		}
		itter = itter->next;
	}
	return (0);
}

int	get_all_heredoc(t_metadata *data, t_simple_cmd *cmd_list)
{
	int		i;

	i = 0;
	while (i < data->cmd_count)
	{
		if (get_heredocs_this_cmd(data, cmd_list))
			return (1);
		i++;
		cmd_list = cmd_list->next;
	}
	return (0);
}
