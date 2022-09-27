/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:44:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/27 20:28:03 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/parcer.h"
#include "../utils/hdr/token_utils.h"
#include "../lexer/hdr/charchecks.h"
#include "../../libft/libft.h"
#include "hdr/separate.h"

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
	int		sep;
	bool	dquote;

	temp = *head;
	dquote = false;
	expanded = NULL;
	while (temp)
	{
		sep = set_separation_limit(temp);
		dquote = set_dquote_flag(dquote, temp, sep);
		if (temp->token_value[0] == '$' && temp->token_label != LESSLESS)
		{
			cnt = 0;
			len = ft_strlen(&temp->token_value[1]);
			while ((*env)[cnt])
			{
				if (!ft_strncmp(&temp->token_value[1], (*env)[cnt], len))
				{
					expanded = expand_string((*env)[cnt], dquote);					
					tokenlst_cut_one(*head, &temp);
					tokenlst_last(expanded)->next = temp;
					if (*head)
						tokenlst_last(*head)->next = expanded;
					else
						*head = expanded;
					break ;
				}
				cnt++;
			}
			if ((*env)[cnt] == NULL && (*head)->token_label > SINGLE_QUOTE)
			{
				tokenlst_cut_one(*head, &temp);
				tokenlst_last(*head)->next = temp;
			}
			printf("%p\n", temp);
			continue ;
		}
		printf("%p\t%p\n", temp, temp->next);
		temp = temp->next;
	}
}

// void	expand_tokens(t_token **current, char ***env)
// {
// 	t_token	*expanded;
// 	t_token	*temp;
// 	bool	dquote;
// 	int		sep;

// 	expanded = NULL;
// 	temp = *current;
// 	dquote = false;
// 	while (temp)
// 	{
// 		sep = set_separation_limit(temp);
// 		dquote = set_dquote_flag(dquote, temp, )
// 	}
// }

void	expand_section(t_token_section *first, char ***env)
{
	t_token_section	*temp;

	if (!first)
		return ;
	temp = first;
	while (temp)
	{
		expand_tokens(&temp->head, env);
		printf("hello\n%p\nhello\n%p\nhello\n%s\nhello\n", temp, temp->head,temp->head->next->token_value);
		temp = temp->next;
	}
	printf("it does get here right?\n");
}

void	parce(t_token *head, char ***env)
{
	t_token_section		*first;
	t_token_section		*temp;
	t_split_cmd_rdir	*split;

	first = tokenlst_split(&head);
	test_split(first);
	temp = first;
	while (temp)
	{
		split = split_cmd_rdir(temp);
		test_split_cmd_rdir(split);
		expand_section(split->cmd_head, env);
		expand_section(split->in_head, env);
		expand_section(split->out_head, env);
		temp = temp->next;
	}
	test_split_cmd_rdir(split);
}
