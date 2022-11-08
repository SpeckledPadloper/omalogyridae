/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm_op.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 12:48:41 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/04 15:12:46 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "hdr/lexer.h"
#include "hdr/charchecks.h"
#include "../utils/hdr/token_utils.h"
#include "../hdr/structs.h"
#include "hdr/fsm.h"

int	fsm_special_char(t_line_nav *lnav, t_token **head, int *exitstatus)
{
	lnav->state = -1;
	if (!add_token_to_list(head, do_special_char(lnav), lnav, exitstatus))
		return (STATE_STXERROR);
	lnav->count = -1;
	return (STATE_START);
}

int	fsm_start(t_line_nav *lnav, t_token **head, int *exitstatus)
{
	if (is_whitespace(lnav->ret[lnav->i]))
	{
		lnav->count = -1;
		return (STATE_WS);
	}
	else if (is_special_char(lnav->ret[lnav->i]))
		return (fsm_special_char(lnav, head, exitstatus));
	else if (lnav->ret[lnav->i] == '\'')
		return (STATE_SQUOTE);
	else if (lnav->ret[lnav->i] == '"')
		return (STATE_DQUOTE);
	else if (lnav->ret[lnav->i] == '$')
		return (set_state_expand(lnav, head, exitstatus));
	else
		return (STATE_COMMON);
}

int	fsm_whitespace(t_line_nav *lnav, t_token **head, int *exitstatus)
{
	while (is_whitespace(lnav->ret[lnav->i]))
		(lnav->i)++;
	if (is_special_char(lnav->ret[lnav->i]))
		return (fsm_special_char(lnav, head, exitstatus));
	else
		lnav->count = 0;
	if (lnav->ret[lnav->i] == '\'')
		return (STATE_SQUOTE);
	else if (lnav->ret[lnav->i] == '"')
		return (STATE_DQUOTE);
	else if (lnav->ret[lnav->i] == '$')
		return (set_state_expand(lnav, head, exitstatus));
	else if (is_end_of_input(lnav->ret[lnav->i]))
	{
		lnav->i--;
		return (STATE_WS);
	}
	else
		return (STATE_COMMON);
}

int	fsm_squote(t_line_nav *lnav, t_token **head, int *exitstatus)
{
	char	*token_value;

	if (lnav->ret[lnav->i] == '\'')
	{
		lnav->count--;
		token_value = allocate_token_value(lnav);
		add_token_to_list(head, token_value, lnav, exitstatus);
		lnav->count = -1;
		return (STATE_WS);
	}
	else
		return (STATE_SQUOTE);
}

int	fsm_common(t_line_nav *lnav, t_token **head, int *exitstatus)
{
	char	*token_value;

	token_value = allocate_token_value(lnav);
	add_token_to_list(head, token_value, lnav, exitstatus);
	lnav->count = -1;
	if (is_whitespace(lnav->ret[lnav->i]))
		return (STATE_WS);
	if (is_special_char(lnav->ret[lnav->i]))
		return (fsm_special_char(lnav, head, exitstatus));
	lnav->count = 0;
	if (lnav->ret[lnav->i] == '\'')
		return (STATE_SQUOTE);
	if (lnav->ret[lnav->i] == '"')
		return (STATE_DQUOTE);
	if (lnav->ret[lnav->i] == '$')
		return (set_state_expand(lnav, head, exitstatus));
	return (STATE_WS);
}
