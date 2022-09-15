/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/15 15:14:31 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <unistd.h>

# define MODE_RW_R_R 0644

typedef enum	s_bash_exitcode
{
	EMPTY = 0,
	CMD_CANT_EXE = 126,
	CMD_NOT_FOUND = 127,
}				t_bash_exitcode;

typedef struct s_fd_list
{
	int	fd_in;
	int	fd_out;
	int	pipe[2];
	int	pipe_to_read;
}					t_fd_list;

typedef struct	s_file
{
	char 			*path_fd;
	int				MODE;
	struct s_file	*next;
}					t_file;

typedef struct s_exec_list_sim
{
	char		**cmd;
	int			index;
	t_file		*infile_list;
	t_file		*outfile_list;
	char		*path_fd_in;
	char		*path_fd_out;
	struct s_exec_list_sim *next;
}				t_exec_list_sim;

typedef struct s_metadata
{
	t_fd_list	*fd_list;
	char		**envp;
	int			child_count;
	int			cmd_count;
	char		*limiter;
	pid_t		lastpid;
	int			err_pipe[2];
	int			exitstatus;
}					t_metadata;


/*-------------------------path builder-------------------------*/

char	*path_builder(t_metadata *data, char *cmd);

/*-------------------------utils-------------------------*/

int	ft_sim_lstsize(t_exec_list_sim *lst);
bool	is_path(char *cmd);
void	close_and_check(int fd);

void	free_2d_array(char **array);

/*-------------------------error handling-------------------------*/

void	print_error_exit(char *errorobject, int errnocopy, int exitcode);



#endif