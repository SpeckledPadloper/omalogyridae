/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 13:38:24 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/28 21:14:23 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/***************************************
 * data structure before expansion     *
 * PIPES 1-N :                         *
 *	COMMAND  : SECTIONS 1-N : TOKENLST *
 *	REDIR_IN : SECTIONS 1-N : TOKENLST *
 *	ReDIR_OUT: SECTIONS 1-N : TOKENLST *
 **************************************/

/* initial input the split_cmd_rdir struct, 
 * to lower lines in the parcer.
 * do each type separate, then loop through the sections,
 * and apply expansion to the token lists.*/

#include "../hdr/structs.h"
#include "../lexer/hdr/lexer.h"
#include <stdbool.h>
#include "hdr/separate.h"
#include "../../libft/libft.h"
#include "../utils/hdr/token_utils.h"
#include "../lexer/hdr/charchecks.h"

#include <stdio.h>

t_token	*expand_to_one(char *env_var)
{
	t_token		*expanded;
	t_line_nav	lnav;

	lnav.ret = env_var;
	lnav.i = ft_strlen(lnav.ret);
	lnav.count = lnav.i;
	expanded = new_node(0, lnav.ret, DOUBLE_QUOTE, &lnav);
	printf("expand_to_one done\n");
	return (expanded);
}

t_token	*expand_to_lst(char *env_var)
{
	t_token		*expanded;
	t_line_nav	lnav;
	char		*new_val;

	expanded = NULL;
	lnav.ret = env_var;
	lnav.i = 0;
	lnav.count = 0;
	while (is_whitespace(lnav.ret[lnav.i]))
		lnav.i++;
	while (lnav.ret[lnav.i])
	{
		if (is_whitespace(lnav.ret[lnav.i]))
		{
			new_val = allocate_token_value(&lnav);
			exp_token_add_back(&expanded, exp_new_token(new_val));
			lnav.count = 0;
			while (is_whitespace(lnav.ret[lnav.i + 1]))
				lnav.i++;
		}
		lnav.i++;
		lnav.count++;
	}
	new_val = allocate_token_value(&lnav);
	exp_token_add_back(&expanded, exp_new_token(new_val));
	return (expanded);
}

t_token	*expand_token(t_token	*current, char ***env, bool quote)
{
	int		len;
	int		cnt;

	cnt = 0;
	len = ft_strlen(current->token_value);
	while ((*env)[cnt])
	{
		if (!ft_strncmp(&current->token_value[1], (*env)[cnt], len - 1))
		{
			if (quote == true)
				return (expand_to_one(ft_strchr((*env)[cnt], '=') + 1));
			else
				return (expand_to_lst(ft_strchr((*env)[cnt], '=') + 1));
		}
		cnt++;
	}
	return (current);
}

void	expand_tokenlst(t_token *head, char ***env)
{
	t_token	*itter;
	t_token	*temp;
	t_token	*expanded;
	bool	quote;
	int		sep;

	itter = head;
	while (itter)
	{
		//printf("itter value = %s\n", itter->token_value);
		sep = set_separation_limit(itter);
		quote = set_quote_state(quote, itter, sep);
		if (itter->token_label == EXPAND)
		{
			expanded = expand_token(itter, env, quote);
			temp = itter;
			itter = itter->next;
			if (temp == head)
			{
				printf("head_last->value: %s\n", head->token_value);
				tokenlst_last(expanded)->next = temp->next;
				head = expanded;
				temp->next = NULL;
				tokenlst_clear(&temp);
			}
			else
			{
				tokenlst_cut_one(&head, &temp);
				tokenlst_last(expanded)->next = temp;
				printf("head_last->value: %s\n", tokenlst_last(head)->token_value);
				tokenlst_last(head)->next = expanded;
			}
			continue ;
		}
		if (itter)
			itter = itter->next;
	}
}

void	expand_section(t_token_section **head, char ***env)
{
	t_token_section	*temp;

	if (!head)
		return ;
	temp = *head;
	while (temp)
	{
		if (temp->head && temp->head->start_pos == -1)
		{
			temp = temp->next;
			continue ;
		}
		else
			expand_tokenlst(temp->head, env);
		temp = temp->next;
	}
}
