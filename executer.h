/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/13 13:55:45 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <unistd.h>

typedef struct s_fd_list
{
	int	fd_in;
	int	fd_out;
	int	pipe[2];
	int	pipe_to_read;
}					t_fd_list;

typedef struct s_exec_list_sim
{
	char		**path;
	int			index;
	char		*path_fd_in;
	char		*path_fd_out;
	t_fd_list	fd_list;
	struct s_exec_list_sim *next;
}				t_exec_list_sim;

typedef struct s_metadata
{
	int		child_count;
	int		cmd_count;
	char	*limiter;
	pid_t	lastpid;
	int		exitstatus;
}					t_metadata;

#endif