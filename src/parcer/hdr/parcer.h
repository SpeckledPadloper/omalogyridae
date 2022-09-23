/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 14:51:11 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/23 18:46:15 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCER_H
# define PARCER_H
# include "../../hdr/structs.h"

typedef enum e_pxstates
{
	STATE_CMD,
	STATE_RDIRIN,
	STATE_RDIROUT
}	t_pxstates;

void				parce(t_token *head, char ***env);
t_split_cmd_rdir	*split_cmd_rdir(t_token_section *current);

#endif