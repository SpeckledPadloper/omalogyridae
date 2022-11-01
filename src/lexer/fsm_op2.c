/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm_op2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 20:28:42 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/01 13:43:46 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "hdr/lexer.h"
#include "hdr/charchecks.h"
#include "../utils/hdr/token_utils.h"
#include "../hdr/structs.h"
#include "hdr/fsm.h"
#include "../../libft/libft.h"

/*fsm_expand still needs to be normed*/

int	set_state_expand(t_line_nav *lnav, t_token **head, t_metadata *data)
{
	lnav->count = 0;
	if (lnav->ret[lnav->i + 1] == '?')
	{
		lnav->i += 2;
		lnav->count += 2;
		add_token_to_list(head, allocate_token_value(lnav), lnav, data);
		lnav->count = 0;
		if (lnav->prev_state == STATE_DQUOTE)
		{
			lnav->count++;
			return (STATE_DQUOTE);
		}
		return (STATE_START);
	}
	return (STATE_EXPAND);
}

int	fsm_dquote(t_line_nav *lnav, t_token **head, t_metadata *data)
{
	if (lnav->ret[lnav->i] == '"')
	{
		lnav->count--;
		add_token_to_list(head, allocate_token_value(lnav), lnav, data);
		lnav->count = -1;
		lnav->prev_state = -1;
		return (STATE_WS);
	}
	else if (lnav->ret[lnav->i] == '$')
	{
		lnav->count -= 1;
		add_token_to_list(head, allocate_token_value(lnav), lnav, data);
		lnav->prev_state = STATE_DQUOTE;
		return (set_state_expand(lnav, head, data));
	}
	else
		return (STATE_DQUOTE);
}

int	fsm_expand(t_line_nav *lnav, t_token **head, t_metadata *data)
{
	add_token_to_list(head, allocate_token_value(lnav), lnav, data);
	lnav->count = -1;
	if (lnav->prev_state == STATE_DQUOTE)
	{
		if (lnav->ret[lnav->i] == '"')
		{
			lnav->prev_state = -1;
			return (STATE_WS);
		}
		else if (lnav->ret[lnav->i] == '$')
			return (set_state_expand(lnav, head, data));
		else
		{
			lnav->count = 1;
			return (STATE_DQUOTE);
		}
	}
	else if (is_special_char(lnav->ret[lnav->i]))
		return (fsm_special_char(lnav, head, data));
	else
	{
		if (!ft_isalnum(lnav->ret[lnav->i]))
			lnav->i--;
		return (STATE_START);
	}
}
