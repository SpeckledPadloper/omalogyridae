/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 12:31:24 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/28 21:04:26 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H
# include "../../lexer/hdr/lexer.h"

t_token			*new_node(int index, char *value, int state, t_line_nav *lnav);
t_token			*tokenlst_last(t_token *lst);
char			*allocate_token_value(t_line_nav *lnav);
bool			add_token_to_list(t_token **head, char *val, int s, t_line_nav *lnav);
void			tokenlst_clear(t_token **head);
void			tokenlst_cut_one(t_token **head, t_token **target);
int				add_token_label(char current, char next_char);

t_token_section	*tokenlst_split(t_token **head);
void			cut_token(t_token **head, t_token **tail);
void			add_section_to_list(t_token_section **first, t_token *head);
t_token_section	*token_section_last(t_token_section *first);
t_token_section	*new_token_section(t_token *head);
t_token_section	*cmdlst_split(t_token **head);
t_token_section	*rdirlst_split(t_token **head, int f1, int f2);
t_token			*exp_new_token(char *value);
void			exp_token_add_back(t_token **head, t_token *new);


#endif
