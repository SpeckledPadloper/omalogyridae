/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm_op2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 20:28:42 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 16:47:06 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/lexer.h"
#include "hdr/charchecks.h"
#include "../utils/hdr/token_utils.h"
#include "../hdr/structs.h"
#include "hdr/fsm.h"
#include "../../libft/libft.h"
#include <stdlib.h>

#include <stdio.h>

/*fsm_expand still needs to be normed*/

int	set_state_expand(t_line_nav *lnav, t_token **head, int *exitstatus)
{
	lnav->count = 0;
	if (lnav->ret[lnav->i + 1] == '?')
	{
		lnav->i += 2;
		lnav->count += 2;
		add_token_to_list(head, allocate_token_value(lnav), lnav, exitstatus);
		if (lnav->prev_state == STATE_DQUOTE)
		{
			lnav->count = 1;
			return (STATE_DQUOTE);
		}
		if (is_whitespace(lnav->ret[lnav->i]))
			lnav->count = -1;
		else
			lnav->count = 0;
		return (STATE_START);
	}
	return (STATE_EXPAND);
}

int	fsm_dquote(t_line_nav *lnav, t_token **head, int *exitstatus)
{
	if (lnav->ret[lnav->i] == '"')
	{
		lnav->count--;
		add_token_to_list(head, allocate_token_value(lnav), lnav, exitstatus);
		lnav->count = -1;
		lnav->prev_state = -1;
		return (STATE_WS);
	}
	else if (lnav->ret[lnav->i] == '$')
	{
		lnav->count -= 1;
		add_token_to_list(head, allocate_token_value(lnav), lnav, exitstatus);
		lnav->prev_state = STATE_DQUOTE;
		return (set_state_expand(lnav, head, exitstatus));
	}
	else
		return (STATE_DQUOTE);
}

static int	fms_exp_to_dq(t_line_nav *lnav, t_token **head, int *exitstatus)
{
	char	*token_value;

	if (lnav->ret[lnav->i] == '"')
	{
		lnav->count = 0;
		token_value = allocate_token_value(lnav);
		if (token_value == NULL)
			token_value = ft_strdup("\0");
		if (token_value == NULL)
			exit(EXIT_FAILURE);
		lnav->state = STATE_DQUOTE;
		add_token_to_list(head, token_value, lnav, exitstatus);
		lnav->count = -1;
		lnav->prev_state = -1;
		return (STATE_WS);
	}
	else if (lnav->ret[lnav->i] == '$')
		return (set_state_expand(lnav, head, exitstatus));
	else
	{
		lnav->count = 1;
		return (STATE_DQUOTE);
	}
}

int	fsm_expand(t_line_nav *lnav, t_token **head, int *exitstatus)
{
	add_token_to_list(head, allocate_token_value(lnav), lnav, exitstatus);
	lnav->count = -1;
	if (lnav->prev_state == STATE_DQUOTE)
		return (fms_exp_to_dq(lnav, head, exitstatus));
	else if (is_special_char(lnav->ret[lnav->i]))
		return (fsm_special_char(lnav, head, exitstatus));
	else
	{
		if (!ft_isalnum(lnav->ret[lnav->i]))
			lnav->i--;
		return (STATE_START);
	}
}
