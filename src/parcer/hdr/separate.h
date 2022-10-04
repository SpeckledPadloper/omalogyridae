/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   separate.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 19:39:12 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/01 19:59:01 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATE_H
# define SEPARATE_H
# include "../../hdr/structs.h"

int		set_state_cio(t_token *temp);
int		set_separation_limit(t_token *temp);
bool	set_quote_state(bool dq, t_token *temp, int sep);
void	free_cmd_rdir(t_split_cmd_rdir	**split);

#endif
