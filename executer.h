/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executer.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/27 14:29:18 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <stdbool.h>
# include <unistd.h>

# define MODE_RW_R_R 0644
# define CNF_BUF_SIZE 18

typedef enum e_open_modes
{
	NONE = -1,
	LESS = 0,
	LESSLESS = 1,
	GREAT = 2,
	GREATGREAT = 3,
}				t_open_modes;

typedef enum e_exit_error_code
{
	EMPTY = 0,
	ERRNO_NO_SUCH_FILE = 2,
	CMD_CANT_EXE = 126,
	CMD_NOT_FOUND = 127,
}				t_exit_error_code;

typedef struct s_fd_list
{
	int	fd_in;
	int	fd_out;
	int	pipe[2];
	int	pipe_to_read;
}					t_fd_list;

typedef struct s_file
{
	char			*filename;
	t_open_modes	mode;
	struct s_file	*next;
}					t_file;

typedef struct s_exec_list_sim
{
	char					**cmd;
	int						index;
	t_file					*infile_list;
	t_file					*outfile_list;
	int						heredoc_pipe[2];
	struct s_exec_list_sim	*next;
}				t_exec_list_sim;

typedef struct s_metadata
{
	t_fd_list	*fd_list;
	char		**envp;
	int			child_count;
	int			cmd_count;
	pid_t		lastpid;
	int			exitstatus;
}					t_metadata;

/*-------------------------executer-------------------------*/

void	executer(t_metadata *meta_data, t_exec_list_sim *cmd_list);

/*-------------------------file handling-------------------------*/

void	open_necessary_infiles(t_metadata *data, t_exec_list_sim *cmd_list);
void	open_necessary_outfiles(t_metadata *data, t_exec_list_sim *cmd_list);
void	redirect_input(t_metadata *data, t_exec_list_sim *cmd_list);
void	redirect_output(t_metadata *data, t_exec_list_sim *cmd_list);
void	close_unused_fd(t_metadata *data, t_exec_list_sim *cmd_list);

/*-------------------------path builder-------------------------*/

char	*path_builder(t_metadata *data, char *cmd);

/*-------------------------utils-------------------------*/

int		ft_sim_lstsize(t_exec_list_sim *lst);
bool	is_path(char *cmd);
void	close_and_check(int fd);

void	free_2d_array(char **array);

/*-------------------------error handling-------------------------*/

void	print_error_exit(char *errorobject, int errnocopy, int exitcode);

/*-------------------------heredoc handling-------------------------*/

void	get_all_heredoc(t_metadata *data, t_exec_list_sim *cmd_list);

#endif
