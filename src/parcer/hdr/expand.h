/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 13:38:32 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/28 17:13:48 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "../../hdr/structs.h"

t_token	*expand_to_one(char *env_var);
t_token	*expand_to_lst(char *env_var);
t_token	*expand_token(t_token	*current, char ***env, bool quote);
void	expand_tokenlst(t_token *head, char ***env);
void	expand_section(t_token_section **head, char ***env);

#endif