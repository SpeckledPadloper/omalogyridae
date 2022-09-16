/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 11:03:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/16 20:28:00 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h> //path max
#include <unistd.h> //getcwd 

#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <string.h>
#include <stdbool.h>
#include "../../libft/libft.h"
#include "hdr/lexer.h"
#include "hdr/fsm.h"
#include "hdr/token_utils.h"
#include "hdr/charchecks.h"

#define KNRM  "\e[0m"
#define KRED  "\e[1;31m"

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

static void	fsm_block(t_line_nav *lnav, t_token **head, int *s, int *ps)
{
	if (*s == STATE_START)
		*s = fsm_start(lnav, head);
	else if (*s == STATE_COMMON)
		*s = fsm_common(lnav, head);
	else if (*s == STATE_WS)
		*s = fsm_whitespace(lnav, head);
	else if (*s == STATE_SQUOTE)
		*s = fsm_squote(lnav, head);
	else if (*s == STATE_DQUOTE)
		*s = fsm_dquote(lnav, head, ps);
	else if (*s == STATE_EXPAND)
		*s = fsm_expand(lnav, head, ps);
}

void	lex(char *ret)
{
	t_token		*head;
	t_line_nav	lnav;
	int			state;
	int			prev_state;
	t_token		*itter;

	lnav.ret = ret;
	lnav.i = 0;
	lnav.count = 0;
	prev_state = -1;
	head = NULL;
	state = STATE_START;
	while (lnav.ret[lnav.i])
	{
		if (is_token_separator(lnav.ret[lnav.i]))
			fsm_block(&lnav, &head, &state, &prev_state);
		else if (!(state == STATE_SQUOTE || state == STATE_DQUOTE \
				|| state == STATE_EXPAND))
			state = STATE_COMMON;
		if (is_end_of_input(lnav.ret[lnav.i + 1]) && state == STATE_COMMON)
		{
			lnav.i++;
			add_token_to_list(&head, allocate_token_value(&lnav), 8, &lnav);
		}
		lnav.i++;
		lnav.count++;
	}
	itter = head;
	while (itter)
	{
		printf("token = %s\t| token_label = %d\t| token_index = %d\t| token_start = %d\t| token_end = %d\t| token_len = %zu\n", itter->token_value, itter->token_label, itter->i, itter->start_pos, itter->end_pos, ft_strlen(itter->token_value));
		itter = itter->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_base_args	*b_args;
	char		ctrl_d;

	b_args = set_base_args(argc, argv, env);
	input = "";
	ctrl_d = '\0';
	while (input != NULL)
	{
		input = readline("SpeckledPadloper> ");
		lex(input);
		add_history(input);
		free(input);
	}
	free(b_args);
}

// int main()
// {
// 	char *ret;
// 	char path_buffer[PATH_MAX];

// 	getcwd(path_buffer, sizeof(path_buffer));
// 	printf("%s\n", path_buffer);
// 	//ret = readline("minishell> ");
// 	ret = "<<hier dit'probeer'ik  is >test";
// 	lex(ret);
// 	while (ret != NULL)
// 	{
// 		ret = readline("SpeckledPadloper> ");
// 		lex(ret);
// 		add_history(ret);
// 		free(ret);
// 	}
// 	free(ret);
// 	exit (0);
// }
