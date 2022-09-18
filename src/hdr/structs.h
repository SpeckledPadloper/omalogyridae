/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:48:05 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/18 20:17:20 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define SHLNAME "SpeckledPadloper"

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

typedef struct s_preexpand
{
	t_token	*head;
	char	*q;
}	t_preexpand;

typedef struct s_simple_command
{
	int						index;
	char					**cmd;
	char					*redir_in;
	char					*redir_out;
	struct s_simple_command	*next;
}	t_simple_command;

#endif
