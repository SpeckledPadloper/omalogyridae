/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:48:05 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/08 16:38:45 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define SHLPROM "SpeckledPadloper> "
# define SHLNAME "SpeckledPadloper"
# define SHLERR "SpeckledPadloper: "
# define NR_BLDINS 7
# include <stdbool.h>
# include <unistd.h>

int	g_exitstatus;

typedef enum e_file_flags
{
	RDIR_AMBIGUOUS = -3,
	RDIR_SINGLE = -2,
	RDIR_DOUBLE = -1
}	t_file_flags;

typedef enum e_exit_error_code
{
	CNF = -1,
	AR = -2,
	IS_DIR = -3,
	NOT_VALID = -4,
	NOT_SUPPORTED = -5,
	NOT_SUPPORTED_BOTH = -6,
	NOT_NUMERIC = -7,
	NOT_DIR = -8,
	TOO_MANY = -9,
	NO_PATH = -10,
	EMPTY = 0,
	ERRNO_NO_SUCH_FILE = 2,
	CMD_CANT_EXE = 126,
	CMD_NOT_FOUND = 127,
}				t_exit_error_code;

typedef struct s_line_nav
{
	char	*ret;
	int		i;
	int		count;
	int		state;
	int		prev_state;
}	t_line_nav;

typedef struct s_token
{
	int				i;
	int				token_label;
	int				start_pos;
	int				end_pos;
	char			*token_value;
	struct s_token	*next;
}					t_token;

typedef struct s_token_section
{
	t_token					*head;
	struct s_token_section	*next;
}	t_token_section;

typedef struct s_split_cmd_rdir
{
	t_token			*cmd_head;
	t_token_section	*in_head;
	t_token_section	*out_head;
}	t_split_cmd_rdir;

typedef struct s_file
{
	char			*filename;
	int				mode;
	struct s_file	*next;
}	t_file;

typedef struct s_simple_cmd
{
	char				**cmd;
	int					index;
	t_file				*infile_list;
	t_file				*outfile_list;
	int					heredoc_pipe[2];
	struct s_simple_cmd	*next;
}	t_simple_cmd;

typedef struct s_fd_list
{
	int	fd_in;
	int	fd_out;
	int	pipe[2];
	int	pipe_to_read;
}					t_fd_list;

typedef struct s_metadata
{
	t_fd_list	*fd_list;
	char		*buildins[NR_BLDINS];
	void		(*fn_buildins[NR_BLDINS])(struct s_metadata *, t_simple_cmd *);
	char		**padloper_envp;
	char		**sorted_print_export;
	bool		env_updated;
	int			envp_size;
	int			envp_space;
	int			child_count;
	int			cmd_count;
	pid_t		lastpid;
	pid_t		heredocpid;
	int			exitstatus;
}					t_metadata;

void	reset_metadata(t_metadata *data, t_fd_list *fd_list);
void	init_metadata(t_metadata *data, t_fd_list *fd_list, char **envp);
int		ft_sim_lstsize(t_simple_cmd *lst);

#endif
