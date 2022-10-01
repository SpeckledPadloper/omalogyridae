/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 14:51:11 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/01 20:10:29 by mteerlin      ########   odam.nl         */
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
int					set_separation_limit(t_token *temp);
void				stitch(t_split_cmd_rdir **current);
t_exec_list_sim		*set_simple_command(t_split_cmd_rdir *current);

#endif