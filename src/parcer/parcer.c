/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:44:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/24 20:18:22 by mteerlin      ########   odam.nl         */
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

	printf("%s\n", var);
	expanded = NULL;
	lnav.ret = ft_strdup(ft_strchr(var, '=') + 1);
	lnav.i = 0;
	lnav.count = 0;
	printf("dquote = %d\n", dquote);
	if (dquote)
	{
		lnav.i = ft_strlen(new_val);
		lnav.count = lnav.i;
		add_token_to_list(&expanded, lnav.ret, STATE_DQUOTE, &lnav);
		printf("%s\n", expanded->token_value);
	}
	else
	{
		while (lnav.ret[lnav.i])
		{
			if (is_whitespace(lnav.ret[lnav.i]))
			{
				printf("is_whitespace\n");
				new_val = allocate_token_value(&lnav);
				printf("new value: %s\n\n", new_val);
				add_token_to_list(&expanded, new_val, STATE_DQUOTE, &lnav);
				tokenlst_last(expanded)->token_label = NO_LABEL;
				lnav.count = -1;
			}
			else if (lnav.ret[lnav.i + 1] == '\0')
			{
				printf("end of line\n");
				lnav.i++;
				lnav.count++;
				new_val = allocate_token_value(&lnav);
				printf("new value: %s\n\n", new_val);
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
		printf("%p\n", expanded);
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
		if (temp->token_label == EXPAND)
		{
			cnt = 0;
			len = ft_strlen(&temp->token_value[1]);
			while ((*env)[cnt])
			{
				if (!ft_strncmp(&temp->token_value[1], (*env)[cnt], len))
				{
					expanded = expand_string((*env)[cnt], dquote);
					write(1, "1\n", 2);
					tokenlst_cut_one(head, &temp);
					write(1, "2\n", 2);
					tokenlst_last(expanded)->next = temp;
					write(1, "3\n", 2);
					tokenlst_last(*head)->next = expanded;
					write(1, "4\n", 2);
					break ;
				}
				cnt++;
			}
			if ((*env)[cnt] == NULL)
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
	t_split_cmd_rdir	*split;
	//t_exec_list_sim		*start;

	first = tokenlst_split(head);
	test_split(first);
	temp = first;
	while (temp)
	{
		// here will come the code to turn each split section into the final list
		// final bits of parcing, expantion, all that.
		split = split_cmd_rdir(temp);
		test_split_cmd_rdir(split);
		expand_tokens(&split->cmd_head, env);
		test_lex(split->cmd_head);
		temp = temp->next;
	}
}
