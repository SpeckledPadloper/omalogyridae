/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fsm_op.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 12:48:41 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/16 20:29:16 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "hdr/lexer.h"
#include "hdr/charchecks.h"
#include "hdr/token_utils.h"

int	fsm_start(t_line_nav *lnav, t_token **head)
{
	if (is_whitespace(lnav->ret[lnav->i]))
		return (STATE_WS);
	else if (is_special_char(lnav->ret[lnav->i]))
	{
		printf("is special char\n");
		add_token_to_list(head, do_special_char(lnav), -1, lnav);
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

int	fsm_whitespace(t_line_nav *lnav, t_token **head)
{
	while (is_whitespace(lnav->ret[lnav->i]))
		(lnav->i)++;
	if (is_special_char(lnav->ret[lnav->i]))
	{
		add_token_to_list(head, do_special_char(lnav), -1, lnav);
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

int	fsm_squote(t_line_nav *lnav, t_token **head)
{
	char	*token_value;

	if (lnav->ret[lnav->i] == '\'')
	{
		lnav->count--;
		token_value = allocate_token_value(lnav);
		add_token_to_list(head, token_value, STATE_SQUOTE, lnav);
		lnav->count = -1;
		return (STATE_WS);
	}
	else
		return (STATE_SQUOTE);
}

int	fsm_dquote(t_line_nav *lnav, t_token **head, int *prev_state)
{
	printf("previous state fsm_dquote = %d\n", *prev_state);
	if (lnav->ret[lnav->i] == '"')
	{
		lnav->count--;
		add_token_to_list(head, allocate_token_value(lnav), STATE_DQUOTE, lnav);
		lnav->count = -1;
		return (STATE_WS);
	}
	else if (lnav->ret[lnav->i] == '$')
	{
		lnav->count -= 1;
		add_token_to_list(head, allocate_token_value(lnav), STATE_DQUOTE, lnav);
		lnav->count = 0;
		*prev_state = STATE_DQUOTE;
		return (STATE_EXPAND);
	}
	else
		return (STATE_DQUOTE);
}
