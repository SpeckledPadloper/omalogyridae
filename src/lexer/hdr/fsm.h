/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 14:04:23 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/31 17:54:23 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSM_H
# define FSM_H
# include "lexer.h"
# include "../../hdr/structs.h"

int	fsm_start(t_line_nav *lnav, t_token **head, t_metadata *data);
int	fsm_whitespace(t_line_nav *lnav, t_token **head, t_metadata *data);
int	fsm_squote(t_line_nav *lnav, t_token **head, t_metadata *data);
int	fsm_dquote(t_line_nav *lnav, t_token **head, t_metadata *data);
int	fsm_expand(t_line_nav *lnav, t_token **head, t_metadata *data);
int	fsm_common(t_line_nav *lnav, t_token **head, t_metadata *data);
int	set_state_expand(t_line_nav *lnav, t_token **head, t_metadata *data);
int	fsm_special_char(t_line_nav *lnav, t_token **head, t_metadata *data);

#endif