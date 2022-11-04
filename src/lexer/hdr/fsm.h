/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 14:04:23 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/04 15:13:43 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSM_H
# define FSM_H
# include "lexer.h"
# include "../../hdr/structs.h"

int	fsm_start(t_line_nav *lnav, t_token **head, int *exitstatus);
int	fsm_whitespace(t_line_nav *lnav, t_token **head, int *exitstatus);
int	fsm_squote(t_line_nav *lnav, t_token **head, int *exitstatus);
int	fsm_dquote(t_line_nav *lnav, t_token **head, int *exitstatus);
int	fsm_expand(t_line_nav *lnav, t_token **head, int *exitstatus);
int	fsm_common(t_line_nav *lnav, t_token **head, int *exitstatus);
int	set_state_expand(t_line_nav *lnav, t_token **head, int *exitstatus);
int	fsm_special_char(t_line_nav *lnav, t_token **head, int *exitstatus);

#endif