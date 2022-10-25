/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 13:38:24 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/25 14:15:54 by mteerlin      ########   odam.nl         */
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
#include "hdr/expand.h"

#include <stdio.h>
#include "../tests/tests.h"

t_token	*exp_to_one(char *env_var, int index)
{
	t_token		*expanded;
	t_line_nav	lnav;

	lnav.ret = ft_strdup(env_var);
	lnav.i = ft_strlen(lnav.ret);
	lnav.count = lnav.i;
	lnav.state = DOUBLE_QUOTE;
	expanded = new_node(index, lnav.ret, &lnav);
	return (expanded);
}

t_token	*exp_to_lst(t_token *current, char *env_var, bool isredir)
{
	t_token		*expanded;
	t_line_nav	lnav;
	t_token		*new;

	expanded = NULL;
	lnav.ret = ft_strdup(env_var);
	lnav.i = 0;
	lnav.count = 0;
	while (is_whitespace(lnav.ret[lnav.i]))
		lnav.i++;
	while (lnav.ret[lnav.i])
	{
		if (is_whitespace(lnav.ret[lnav.i]))
		{
			new = exp_new_token(allocate_token_value(&lnav));
			new->i = current->i;
			exp_token_add_back(&expanded, new);
			lnav.count = -1;
			while (is_whitespace(lnav.ret[lnav.i + 1]))
				lnav.i++;
		}
		lnav.i++;
		lnav.count++;
	}
	new = exp_new_token(allocate_token_value(&lnav));
	new->i = current->i;
	exp_token_add_back(&expanded, new);
	if (isredir && expanded->next)
		expanded->token_label = RDIR_AMBIGUOUS;
	return (expanded);
}

t_token	*expand_token(t_token *current, char ***env, bool quote, bool isrdir)
{
	int		len;
	int		cnt;
	t_token	*ret;

	cnt = 0;
	len = ft_strlen(current->token_value);
	while ((*env)[cnt])
	{
		if (!ft_strncmp(&current->token_value[1], (*env)[cnt], len - 1))
		{
			if (quote == true)
				ret = exp_to_one(ft_strchr((*env)[cnt], '=') + 1, current->i);
			else
				ret = exp_to_lst(current, ft_strchr((*env)[cnt], '=') + 1, isrdir);
			return (ret);
		}
		cnt++;
	}
	if (isrdir)
	{
		current->token_label = RDIR_AMBIGUOUS;
		return (current);
	}
	return (exp_new_token(NULL));
}

void	expand_tokenlst(t_token_section **current, char ***env, bool isredir)
{
	t_token	*itter;
	t_token	*expandlst;
	bool	quote;
	int		sep;

	itter = (*current)->head;
	quote = false;
	expandlst = NULL;
	while (itter)
	{
		sep = set_separation_limit(itter);
		quote = set_quote_state(quote, itter, sep);
		if (itter->token_label == EXPAND)
			exp_token_add_back(&expandlst, expand_token(itter, env, quote, isredir));
		if (itter)
			itter = itter->next;
	}
	if (isredir && is_ambiguous_rdir(expandlst))
	{
		tokenlst_clear(&expandlst);
		(*current)->head->token_label = RDIR_AMBIGUOUS;
		return ;
	}
	link_expand_tokens(&(*current)->head, &expandlst);
}

void	expand_section(t_token_section **head, char ***env, bool isredir)
{
	t_token_section	*temp;

	if (!head)
		return ;
	temp = *head;
	while (temp && temp->head)
	{
		if (temp->head->start_pos == -1)
		{
			temp->head->token_label = RDIR_DOUBLE;
			temp = temp->next;
			continue ;
		}
		else
			expand_tokenlst(&temp, env, isredir);
		temp = temp->next;
	}
}
