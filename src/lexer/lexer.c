/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 11:03:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/09 14:41:09 by mteerlin      ########   odam.nl         */
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
#include "../utils/hdr/line_navigation.h"

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

static void	fsm_block(t_line_nav *lnav, t_token **head, int *exitstatus)
{
	if (lnav->state == STATE_START)
		lnav->state = fsm_start(lnav, head, exitstatus);
	else if (lnav->state == STATE_COMMON)
		lnav->state = fsm_common(lnav, head, exitstatus);
	else if (lnav->state == STATE_WS)
		lnav->state = fsm_whitespace(lnav, head, exitstatus);
	else if (lnav->state == STATE_SQUOTE)
		lnav->state = fsm_squote(lnav, head, exitstatus);
	else if (lnav->state == STATE_DQUOTE)
		lnav->state = fsm_dquote(lnav, head, exitstatus);
	else if (lnav->state == STATE_EXPAND)
		lnav->state = fsm_expand(lnav, head, exitstatus);
}

static void	end_of_input(t_token **head, t_line_nav *lnav, int *exitstatus)
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
		add_token_to_list(head, allocate_token_value(lnav), lnav, exitstatus);
	}
	else
		add_token_to_list(head, NULL, lnav, exitstatus);
}

int	determine_lex_action(t_token **head, t_line_nav *lnav, int *exitstatus)
{
	if (lnav->state == STATE_EXPAND && \
		(!ft_isalnum(lnav->ret[lnav->i]) && !(lnav->ret[lnav->i] == '_')))
		fsm_block(lnav, head, exitstatus);
	else if (is_token_separator(lnav->ret[lnav->i]))
		fsm_block(lnav, head, exitstatus);
	else if (lnav->state <= STATE_WS || lnav->state == STATE_COMMON)
		lnav->state = STATE_COMMON;
	if (is_end_of_input(lnav->ret[lnav->i + 1]))
	{
		end_of_input(head, lnav, exitstatus);
		return (0);
	}
	if (lnav->state == STATE_STXERROR)
	{
		tokenlst_clear(head);
		return (0);
	}
	return (1);
}

t_token	*lex(char *ret, int *exitstatus)
{
	t_token		*head;
	t_line_nav	lnav;

	init_lnav(&lnav, ret);
	head = NULL;
	while (lnav.ret[lnav.i])
	{
		if (!determine_lex_action(&head, &lnav, exitstatus))
			break ;
		lnav.i++;
		lnav.count++;
	}
	if (head && tokenlst_last(head)->token_label <= PIPE)
		syntax_error("newline", &head, exitstatus);
	return (head);
}
