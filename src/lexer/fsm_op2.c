/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm_op2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 20:28:42 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/29 15:45:08 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "hdr/lexer.h"
#include "hdr/charchecks.h"
#include "../utils/hdr/token_utils.h"
#include "../hdr/structs.h"

/*fsm_expand still needs to be normed*/
int	fsm_expand(t_line_nav *lnav, t_token **head, int *prev_state)
{
	add_token_to_list(head, allocate_token_value(lnav), STATE_EXPAND, lnav);
	lnav->count = -1;
	//printf("\nstate_dquote = %d\nstate_previous = %d\n\n", STATE_DQUOTE, *prev_state);
	if (*prev_state == STATE_DQUOTE)
	{
		if (lnav->ret[lnav->i] == '"')
		{
			*prev_state = -1;
			return (STATE_WS);
		}
		else if (lnav->ret[lnav->i] == '$')
		{
			lnav->count = 0;
			return (STATE_EXPAND);
		}
		else
		{
			lnav->count = 1;
			return (STATE_DQUOTE);
		}
	}
	else if (is_special_char(lnav->ret[lnav->i]))
	{
		add_token_to_list(head, do_special_char(lnav), -1, lnav);
		lnav->count = -1;
		return (STATE_WS);
	}
	else
	{
		if (lnav->ret[lnav->i] == '"' || lnav->ret[lnav->i] == '\'' \
			|| lnav->ret[lnav->i] == '$')
			lnav->i--;
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
	if (is_special_char(lnav->ret[lnav->i]))
	{
		add_token_to_list(head, do_special_char(lnav), -1, lnav);
		lnav->count = -1;
		return (STATE_WS);
	}
	lnav->count = 0;
	if (lnav->ret[lnav->i] == '\'')
		return (STATE_SQUOTE);
	if (lnav->ret[lnav->i] == '"')
		return (STATE_DQUOTE);
	if (lnav->ret[lnav->i] == '$')
		return (STATE_EXPAND);
	return (STATE_WS);
}
