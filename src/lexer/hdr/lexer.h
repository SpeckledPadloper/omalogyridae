/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/25 14:08:51 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdbool.h>
# include "../../hdr/structs.h"

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
	STATE_COMMON,
	STATE_STXERROR
}	t_fin_state;

typedef struct s_line_nav
{
	char	*ret;
	int		i;
	int		count;
	int		state;
}	t_line_nav;

bool		is_special_char(char current);
bool		is_end_of_input(char current_plus_one);
bool		is_token_separator(char current);
bool		is_literal(char current);
bool		is_closing_char(char current, int token_label);

char		*do_special_char(t_line_nav *lnav);

t_token		*lex(char *ret, t_metadata *data);
t_base_args	*set_base_args(int argc, char **argv, char **env);

#endif