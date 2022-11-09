/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expandv2.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 12:35:12 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 16:00:20 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDV2_H
# define EXPANDV2_H
# include "../../hdr/structs.h"
# include <stdbool.h>

void	expand_iolst(t_token_section **head, char ***env, t_metadata *data);
t_token	*expand_tokenlst(t_token *head, char ***env, bool rd, t_metadata *data);
void	link_expand_tokens(t_token **head, t_token **expand);
t_token	*expand_to_null(void);

#endif