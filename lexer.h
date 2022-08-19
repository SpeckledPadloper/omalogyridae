/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/08/17 15:26:23 by lwiedijk      ########   odam.nl         */
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
	HEREDOC_LIM,
	GREAT,
	GREATGREAT,
	PIPE,
	FILENAME_IN,
	FILENAME_OUT,
	COMMAND,
	CMD_ARG,
	//CMD_FLAG,
	//LITERAL,
	//LITERAL_EXPAND,
	//verschil tussen flag en cmd_arg word dus door programma gehandeld, en 
	//literal is deel van een token, niet perce 1 op zich
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


#endif