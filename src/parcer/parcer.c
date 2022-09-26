/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:44:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/26 19:35:37 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/parcer.h"
#include "../utils/hdr/token_utils.h"
#include "../lexer/hdr/charchecks.h"
#include "../../libft/libft.h"

#include "../tests/tests.h" //for testing, remove before handin
#include <stdio.h>
#include <unistd.h>

t_token	*expand_string(char *var, bool dquote)
{
	t_line_nav	lnav;
	t_token		*expanded;
	char		*new_val;

	expanded = NULL;
	lnav.ret = ft_strdup(ft_strchr(var, '=') + 1);
	lnav.i = 0;
	lnav.count = 0;
	if (dquote)
	{
		lnav.i = ft_strlen(var);
		lnav.count = lnav.i;
		add_token_to_list(&expanded, lnav.ret, STATE_DQUOTE, &lnav);
	}
	else
	{
		while (lnav.ret[lnav.i])
		{
			if (is_whitespace(lnav.ret[lnav.i]))
			{
				new_val = allocate_token_value(&lnav);
				add_token_to_list(&expanded, new_val, STATE_DQUOTE, &lnav);
				tokenlst_last(expanded)->token_label = NO_LABEL;
				lnav.count = -1;
			}
			else if (lnav.ret[lnav.i + 1] == '\0')
			{
				lnav.i++;
				lnav.count++;
				new_val = allocate_token_value(&lnav);
				add_token_to_list(&expanded, new_val, STATE_DQUOTE, &lnav);
				tokenlst_last(expanded)->token_label = NO_LABEL;
				lnav.count = -1;
			}
			while (is_whitespace(lnav.ret[lnav.i]) \
					&& is_whitespace(lnav.ret[lnav.i + 1]))
			{
				lnav.i++;
				lnav.count++;
			}
			lnav.i++;
			lnav.count++;
		}
	}
	return (expanded);
}

void	expand_tokens(t_token **head, char ***env)
{
	t_token	*expanded;
	t_token	*temp;
	int		cnt;
	int		len;
	int		end_prev;
	int		sep;
	bool	dquote;

	temp = *head;
	end_prev = 0;
	sep = 2;
	dquote = false;
	expanded = NULL;
	while (temp)
	{
		if (dquote == false && temp->token_label == DOUBLE_QUOTE)
			dquote = true;
		else if (dquote == true && temp->token_label != DOUBLE_QUOTE \
				&& (temp->start_pos - end_prev) >= (sep - 1))
			dquote = false;
		if (temp->token_value[0] == '$' && temp->token_label != LESSLESS)
		{
			cnt = 0;
			len = ft_strlen(&temp->token_value[1]);
			while ((*env)[cnt])
			{
				if (!ft_strncmp(&temp->token_value[1], (*env)[cnt], len))
				{
					expanded = expand_string((*env)[cnt], dquote);
					tokenlst_cut_one(head, &temp);
					tokenlst_last(expanded)->next = temp;
					tokenlst_last(*head)->next = expanded;
					break ;
				}
				cnt++;
			}
			if ((*env)[cnt] == NULL && (*head)->token_label > SINGLE_QUOTE)
			{
				tokenlst_cut_one(head, &temp);
				tokenlst_last(*head)->next = temp;
			}
		}
		if (temp)
		{
			end_prev = temp->end_pos;
			sep = set_separation_limit(temp);
			temp = temp->next;
		}
	}
}

void	parce(t_token *head, char ***env)
{
	t_token_section		*first;
	t_token_section		*temp;
	t_token_section		*temp2;
	t_split_cmd_rdir	*split;
	// t_exec_list_sim		*start;

	first = tokenlst_split(&head);
	test_split(first);
	temp = first;
	while (temp)
	{
		split = split_cmd_rdir(temp);
		test_split_cmd_rdir(split);
		expand_tokens(&split->cmd_head, env);
		temp2 = split->in_head;
		while (temp2)
		{
			printf("temp 2 engaged\n");
			expand_tokens(&split->in_head->head, env);
			printf("how many get after the expansion?\n");
			temp2 = temp2->next;
		}
		printf("\n\n\n");
		test_lex(split->cmd_head);
		printf("\n\n\n");
		if (split && split->in_head)
			test_lex(split->in_head->head);
		temp = temp->next;
	}
}
