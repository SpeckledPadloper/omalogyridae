/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 14:51:11 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 18:06:18 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCER_H
# define PARCER_H
# include "../../hdr/structs.h"
# include "../../hdr/ms_enums.h"
# include "../../utils/hdr/token_utils.h"

t_split_cmd_rdir	*split_cmd_rdir(t_token_section *current);
int					set_separation_limit(t_token *temp);
void				stitch_section(t_token_section **current);
t_simple_cmd		*set_simple_command(t_split_cmd_rdir *current);

#endif