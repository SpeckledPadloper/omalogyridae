/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 13:38:32 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/31 20:06:27 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "../../hdr/structs.h"
# include <stdbool.h>

typedef struct e_expflag
{
	bool	quote;
	bool	isredir;
}	t_expflag;

t_token	*exp_to_one(char *env_var, int index);
t_token	*exp_to_lst(t_token *current, char *env_var, bool isredir);
t_token	*expand_token(t_token *current, char ***env, \
						t_expflag *exflag, t_metadata *data);
void	expand_tokenlst(t_token_section **head, char ***env, \
						bool isredir, t_metadata *data);
void	expand_section(t_token_section **head, char ***env, \
						bool isredir, t_metadata *data);
void	link_expand_tokens(t_token **head, t_token **expand);
bool	is_ambiguous_rdir(t_token *current);

#endif