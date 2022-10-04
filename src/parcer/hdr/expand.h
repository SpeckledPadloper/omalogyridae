/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 13:38:32 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/01 15:26:05 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "../../hdr/structs.h"

t_token	*expand_to_one(char *env_var);
t_token	*expand_to_lst(char *env_var);
t_token	*expand_token(t_token	*current, char ***env, bool quote);
void	expand_tokenlst(t_token **head, char ***env, bool isredir);
void	expand_section(t_token_section **head, char ***env, bool isredir);
void	link_expand_tokens(t_token **head, t_token **temp, t_token **expand);

#endif