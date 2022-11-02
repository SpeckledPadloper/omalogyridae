/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 11:03:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/01 17:09:37 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h> //path max
#include <unistd.h> //getcwd 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <string.h>
#include <stdbool.h>
#include "../../libft/libft.h"
#include "hdr/lexer.h"
#include "hdr/fsm.h"
#include "../utils/hdr/token_utils.h"
#include "hdr/charchecks.h"
#include "../hdr/structs.h"
#include "hdr/errors.h"

#include "../tests/tests.h" //for testing, remove before handin.

char	*do_special_char(t_line_nav *lnav)
{
	char		*token;

	lnav->count = 1;
	token = NULL;
	if ((lnav->ret[lnav->i] == '>' && lnav->ret[lnav->i + 1] == '>')
		|| (lnav->ret[lnav->i] == '<' && lnav->ret[lnav->i + 1] == '<'))
	{
		lnav->count++;
		lnav->i++;
	}
	lnav->i++;
	token = allocate_token_value(lnav);
	lnav->i--;
	return (token);
}

static void	fsm_block(t_line_nav *lnav, t_token **head, t_metadata *data)
{
	if (lnav->state == STATE_START)
		lnav->state = fsm_start(lnav, head, data);
	else if (lnav->state == STATE_COMMON)
		lnav->state = fsm_common(lnav, head, data);
	else if (lnav->state == STATE_WS)
		lnav->state = fsm_whitespace(lnav, head, data);
	else if (lnav->state == STATE_SQUOTE)
		lnav->state = fsm_squote(lnav, head, data);
	else if (lnav->state == STATE_DQUOTE)
		lnav->state = fsm_dquote(lnav, head, data);
	else if (lnav->state == STATE_EXPAND)
		lnav->state = fsm_expand(lnav, head, data);
}

static void	end_of_input(t_token **head, t_line_nav *lnav, t_metadata *data)
{
	if (lnav->state == STATE_SQUOTE || lnav->state == STATE_DQUOTE \
		|| (lnav->state == STATE_EXPAND && lnav->prev_state == STATE_DQUOTE))
	{
		write(2, SHLNAME, ft_strlen(SHLNAME));
		if (lnav->state == STATE_SQUOTE)
			write(2, "'", 1);
		else if (lnav->state == STATE_DQUOTE \
				|| lnav->prev_state == STATE_DQUOTE)
			write(2, "\"", 1);
		write(2, "'\n", 2);
		if (*head != NULL)
			tokenlst_clear(head);
	}
	else if (lnav->state == STATE_COMMON || lnav->state == STATE_EXPAND)
	{
		lnav->i++;
		lnav->count++;
		add_token_to_list(head, allocate_token_value(lnav), lnav, data);
	}
	else
		add_token_to_list(head, NULL, lnav, data);
}

void	init_lnav(t_line_nav *lnav, char *val)
{
	lnav->ret = val;
	lnav->i = 0;
	lnav->count = 0;
	lnav->state = STATE_START;
	lnav->prev_state = -1;
}

int	determine_lex_action(t_token **head, t_line_nav *lnav, t_metadata *data)
{
	if (lnav->state == STATE_EXPAND && \
		(!ft_isalnum(lnav->ret[lnav->i]) && !(lnav->ret[lnav->i] == '_')))
		fsm_block(lnav, head, data);
	else if (is_token_separator(lnav->ret[lnav->i]))
		fsm_block(lnav, head, data);
	else if (lnav->state <= STATE_WS || lnav->state == STATE_COMMON)
		lnav->state = STATE_COMMON;
	if (is_end_of_input(lnav->ret[lnav->i + 1]))
	{
		end_of_input(head, lnav, data);
		return (0);
	}
	if (lnav->state == STATE_STXERROR)
	{
		tokenlst_clear(head);
		return (0);
	}
	return (1);
}

t_token	*lex(char *ret, t_metadata *data)
{
	t_token		*head;
	t_line_nav	lnav;

	init_lnav(&lnav, ret);
	head = NULL;
	while (lnav.ret[lnav.i])
	{
		if (!determine_lex_action(&head, &lnav, data))
			break ;
		lnav.i++;
		lnav.count++;
	}
	// test_lex(head);
	if (head && tokenlst_last(head)->token_label <= PIPE)
		syntax_error("newline", &head, data);
	return (head);
}
