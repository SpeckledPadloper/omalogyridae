/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 11:03:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/04 18:10:36 by mteerlin      ########   odam.nl         */
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

t_base_args	*set_base_args(int argc, char **argv, char **env)
{
	t_base_args	*b_args;

	b_args = malloc(sizeof(t_base_args));
	b_args->argc = argc;
	b_args->argv = argv;
	b_args->env = env;
	return (b_args);
}

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

static void	fsm_block(t_line_nav *lnav, t_token **head, int *state, int *ps)
{
	if (*state == STATE_START)
		*state = fsm_start(lnav, head);
	else if (*state == STATE_COMMON)
		*state = fsm_common(lnav, head);
	else if (*state == STATE_WS)
		*state = fsm_whitespace(lnav, head);
	else if (*state == STATE_SQUOTE)
		*state = fsm_squote(lnav, head);
	else if (*state == STATE_DQUOTE)
		*state = fsm_dquote(lnav, head, ps);
	else if (*state == STATE_EXPAND)
		*state = fsm_expand(lnav, head, ps);
}

static void	end_of_input(t_token **head, t_line_nav *lnav, int state, int ps)
{
	if (state == STATE_SQUOTE || state == STATE_DQUOTE \
		|| (state == STATE_EXPAND && ps == STATE_DQUOTE))
	{
		write(2, SHLNAME, ft_strlen(SHLNAME));
		write(2, ": unexpecter EOF while looking for matching '", 45);
		if (state == STATE_SQUOTE)
			write(2, "'", 1);
		else if (state == STATE_DQUOTE || ps == STATE_DQUOTE)
			write(2, "\"", 1);
		write(2, "'\n", 2);
		if (*head != NULL)
			tokenlst_clear(head);
	}
	else if (state == STATE_COMMON || state == STATE_EXPAND)
	{
		lnav->i++;
		lnav->count++;
		add_token_to_list(head, allocate_token_value(lnav), 8, lnav);
	}
}

t_token	*lex(char *ret)
{
	t_token		*head;
	t_line_nav	lnav;
	int			state;
	static int	prev_state = -1;

	lnav.ret = ret;
	lnav.i = 0;
	lnav.count = 0;
	head = NULL;
	state = STATE_START;
	while (lnav.ret[lnav.i])
	{
		if (is_token_separator(lnav.ret[lnav.i]))
			fsm_block(&lnav, &head, &state, &prev_state);
		else if (state <= STATE_WS || state == STATE_COMMON)
			state = STATE_COMMON;
		if (is_end_of_input(lnav.ret[lnav.i + 1]))
			end_of_input(&head, &lnav, state, prev_state);
		if (state == STATE_STXERROR)
		{
			tokenlst_clear(&head);
			break ;
		}
		lnav.i++;
		lnav.count++;
	}
	if (head && tokenlst_last(head)->token_label <= PIPE)
	{
		syntax_error("newline");
		tokenlst_clear(&head);
	}
	//test_lex(head);
	printf("\n");
	return (head);
}
