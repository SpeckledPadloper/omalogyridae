/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 13:38:32 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 20:54:59 by mteerlin      ########   odam.nl         */
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

void	expand_iolst(t_token_section **head, char ***env, t_metadata *data);
t_token	*expand_tokenlst(t_token *head, char ***env, bool rd, t_metadata *data);
void	link_expand_tokens(t_token **head, t_token **expand);
t_token	*expand_to_null(t_token *current);

#endif