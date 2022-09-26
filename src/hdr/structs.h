/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:48:05 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/26 15:07:59 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define SHLNAME "SpeckledPadloper"
# include <stdbool.h>

typedef enum e_file_flags
{
	RDIR_AMBIGUOUS,
	RDIR_SINGLE,
	RDIR_DOUBLE
}	t_file_flags;

typedef struct s_base_args
{
	int		argc;
	char	**argv;
	char	**env;
}	t_base_args;

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

typedef struct s_exec_list_sim
{
	char					**cmd;
	int						index;
	t_file					*infile_list;
	t_file					*outfile_list;
	int						heredoc_pipe[2];
	struct s_exec_list_sim	*next;
}	t_exec_list_sim;

#endif
