/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/08/24 17:01:35 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define TOKENCHAR "<>\"'|"

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
	struct s_token	*stitch;
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

t_token	*new_node(int index, int label, char *value);
t_token	*tokenlst_last(t_token *lst);
char	*allocate_token_value(char *ret, int count, int i);
void	add_token_to_list(t_token **head, char *token_value, int *token_label);
int		add_token_label(char current, char next_char);

bool	is_special_char(char current);
bool	is_end_of_input(char current_plus_one);
bool	is_token_separator(char current);
bool	is_literal(char current);
bool	is_closing_char(char current, int token_label);

#endif