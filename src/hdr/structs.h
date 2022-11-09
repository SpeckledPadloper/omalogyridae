/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:48:05 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 20:35:03 by mteerlin      ########   odam.nl         */
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
	int			exitprev;
}					t_metadata;

void	reset_metadata(t_metadata *data, t_fd_list *fd_list);
void	init_metadata(t_metadata *data, t_fd_list *fd_list, char **envp);
int		ft_sim_lstsize(t_simple_cmd *lst);

#endif
