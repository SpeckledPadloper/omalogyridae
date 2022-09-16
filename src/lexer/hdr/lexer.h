/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/16 18:48:23 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdbool.h>

typedef enum e_token_label
{
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	EXPAND,
	NO_LABEL
}		t_token_label;

typedef enum e_fin_states
{
	STATE_START,
	STATE_WS,
	STATE_SQUOTE,
	STATE_DQUOTE,
	STATE_EXPAND,
	STATE_COMMON
}	t_fin_state;

typedef struct s_label_flag
{
	bool	single_quote;
	bool	double_quote;
}				t_label_flag;

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

typedef struct s_line_nav
{
	char	*ret;
	int		i;
	int		count;
}	t_line_nav;

typedef struct s_simple_command
{
	int						index;
	char					**cmd;
	char					*redir_in;
	char					*redir_out;
	struct s_simple_command	*next;
}	t_simple_command;

bool	is_special_char(char current);
bool	is_end_of_input(char current_plus_one);
bool	is_token_separator(char current);
bool	is_literal(char current);
bool	is_closing_char(char current, int token_label);

char	*do_special_char(t_line_nav *lnav);

int		fsm_start(t_line_nav *lnav, t_token **head);
int		fsm_whitespace(t_line_nav *lnav, t_token **head);
int		fsm_squote(t_line_nav *lnav, t_token **head);
int		fsm_dquote(t_line_nav *lnav, t_token **head, int *prev_state);
int		fsm_expand(t_line_nav *lnav, t_token **head, int *prev_state);
int		fsm_common(t_line_nav *lnav, t_token **head);

#endif