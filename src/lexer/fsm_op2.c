/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm_op2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 20:28:42 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/16 20:29:02 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "hdr/lexer.h"
#include "hdr/charchecks.h"
#include "hdr/token_utils.h"

int	fsm_expand(t_line_nav *lnav, t_token **head, int *prev_state)
{
	add_token_to_list(head, allocate_token_value(lnav), STATE_EXPAND, lnav);
	if (*prev_state == STATE_DQUOTE)
	{
		lnav->count = 1;
		if (lnav->ret[lnav->i] == '"')
		{
			lnav->count = -1;
			return (STATE_WS);
		}
		else
			return (STATE_DQUOTE);
	}
	else if (is_special_char(lnav->ret[lnav->i]))
	{
		add_token_to_list(head, do_special_char(lnav), -1, lnav);
		lnav->count = -1;
		return (STATE_WS);
	}
	else
	{
		lnav->count = -1;
		if (lnav->ret[lnav->i] == '"' || lnav->ret[lnav->i] == '\'')
			lnav->i--;
		else
			lnav->count = 0;
		return (STATE_WS);
	}
}

int	fsm_common(t_line_nav *lnav, t_token **head)
{
	char	*token_value;

	token_value = allocate_token_value(lnav);
	add_token_to_list(head, token_value, STATE_COMMON, lnav);
	lnav->count = -1;
	if (is_whitespace(lnav->ret[lnav->i]))
		return (STATE_WS);
	else if (is_special_char(lnav->ret[lnav->i]))
	{
		add_token_to_list(head, do_special_char(lnav), -1, lnav);
		return (STATE_WS);
	}
	if (lnav->ret[lnav->i] == '\'')
	{
		lnav->count++;
		return (STATE_SQUOTE);
	}
	if (lnav->ret[lnav->i] == '"')
	{
		lnav->count++;
		return (STATE_DQUOTE);
	}
	if (lnav->ret[lnav->i] == '$')
		return (STATE_EXPAND);
	return (STATE_WS);
}