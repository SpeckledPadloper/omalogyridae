/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/08/23 14:43:51 by mteerlin      ########   odam.nl         */
=======
/*   Updated: 2022/08/23 12:07:23 by lwiedijk      ########   odam.nl         */
>>>>>>> 44cec2f9ee905b0b22e9c8369a5173da428565aa
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum e_token_label
{
	NO_LABEL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT,
	PIPE,
}		t_token_label;

typedef struct s_token
{
	int				i;
	int				token_label;
	char			*token_value;
	struct s_token	*next;
}					t_token;

typedef struct s_label_flag
{
	bool	single_quote;
	bool	double_quote;
}				t_label_flag;

typedef struct s_simple_command
{
	int		index;
	char	**cmd;
	char	*redir_in;
	char	*redir_out;
}	t_simple_command;

#endif