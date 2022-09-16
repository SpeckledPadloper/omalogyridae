/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 12:31:24 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/16 19:58:19 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H
# include "lexer.h"

t_token	*new_node(int index, char *value, int state, t_line_nav *lnav);
t_token	*tokenlst_last(t_token *lst);
char	*allocate_token_value(t_line_nav *lnav);
void	add_token_to_list(t_token **head, char *val, int s, t_line_nav *lnav);
int		add_token_label(char current, char next_char);

#endif