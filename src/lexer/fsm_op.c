/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm_op.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 12:48:41 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/26 13:40:07 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "hdr/lexer.h"
#include "hdr/charchecks.h"
#include "../utils/hdr/token_utils.h"
#include "../hdr/structs.h"

int	fsm_start(t_line_nav *lnav, t_token **head, t_metadata *data)
{
	if (is_whitespace(lnav->ret[lnav->i]))
	{
		lnav->count = -1;
		return (STATE_WS);
	}
	else if (is_special_char(lnav->ret[lnav->i]))
	{
		lnav->state = -1;
		if (!add_token_to_list(head, do_special_char(lnav), lnav, data))
			return (STATE_STXERROR);
		lnav->count = -1;
		return (STATE_WS);
	}
	else if (lnav->ret[lnav->i] == '\'')
		return (STATE_SQUOTE);
	else if (lnav->ret[lnav->i] == '"')
		return (STATE_DQUOTE);
	else if (lnav->ret[lnav->i] == '$')
		return (STATE_EXPAND);
	else
		return (STATE_COMMON);
}

int	fsm_whitespace(t_line_nav *lnav, t_token **head, t_metadata *data)
{
	while (is_whitespace(lnav->ret[lnav->i]))
		(lnav->i)++;
	if (is_special_char(lnav->ret[lnav->i]))
	{
		lnav->state = -1;
		if (!add_token_to_list(head, do_special_char(lnav), lnav, data))
			return (STATE_STXERROR);
		lnav->count = -1;
		return (STATE_WS);
	}
	else
		lnav->count = 0;
	if (lnav->ret[lnav->i] == '\'')
		return (STATE_SQUOTE);
	else if (lnav->ret[lnav->i] == '"')
		return (STATE_DQUOTE);
	else if (lnav->ret[lnav->i] == '$')
		return (STATE_EXPAND);
	else
		return (STATE_COMMON);
}

int	fsm_squote(t_line_nav *lnav, t_token **head, t_metadata *data)
{
	char	*token_value;

	if (lnav->ret[lnav->i] == '\'')
	{
		lnav->count--;
		token_value = allocate_token_value(lnav);
		add_token_to_list(head, token_value, lnav, data);
		lnav->count = -1;
		return (STATE_WS);
	}
	else
		return (STATE_SQUOTE);
}

int	fsm_dquote(t_line_nav *lnav, t_token **head, int *pstate, t_metadata *data)
{
	if (lnav->ret[lnav->i] == '"')
	{
		lnav->count--;
		add_token_to_list(head, allocate_token_value(lnav), lnav, data);
		lnav->count = -1;
		*pstate = -1;
		return (STATE_WS);
	}
	else if (lnav->ret[lnav->i] == '$')
	{
		lnav->count -= 1;
		add_token_to_list(head, allocate_token_value(lnav), lnav, data);
		lnav->count = 0;
		*pstate = STATE_DQUOTE;
		return (STATE_EXPAND);
	}
	else
		return (STATE_DQUOTE);
}
