/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 14:24:48 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 11:32:50 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../libft/libft.h"
#include "hdr/separate.h"
#include "../hdr/ms_enums.h"
#include "../utils/hdr/token_utils.h"
#include "hdr/expand.h"
#include "../executer/hdr/executer.h"
#include <stdlib.h>

#include <stdio.h>

static t_token	*expand_to_one(char *env_var, t_token *current)
{
	t_token		*expanded;
	t_line_nav	lnav;
	char		*eq_shift;

	lnav.i = 0;
	eq_shift = ft_strchr(env_var, '=');
	lnav.ret = ft_strdup(eq_shift + 1);
	if (lnav.ret == NULL)
		exit(EXIT_FAILURE);
	lnav.i = ft_strlen(lnav.ret);
	lnav.count = lnav.i;
	lnav.state = DOUBLE_QUOTE;
	expanded = exp_new_token(lnav.ret);
	expanded->start_pos = current->start_pos;
	expanded->end_pos = current->end_pos;
	return (expanded);
}

static t_token	*expand_exitstatus(int exitstatus, t_token *current)
{
	t_token		*expanded;
	char		*exitstr;
	t_line_nav	lnav;

	lnav.i = 0;
	lnav.ret = ft_itoa(exitstatus);
	if (lnav.ret == NULL)
		exit(EXIT_FAILURE);
	lnav.i = ft_strlen(lnav.ret);
	lnav.count = lnav.i;
	lnav.state = DOUBLE_QUOTE;
	expanded = exp_new_token(lnav.ret);
	expanded->start_pos = current->start_pos;
	expanded->end_pos = current->end_pos;
	return (expanded);
}

static t_token	*expand_token(t_token *current, char ***env, t_metadata *data)
{
	int		len;
	int		idx;
	char	*emptycheck;

	idx = 0;
	len = ft_strlen(&current->token_value[1]);
	if (current->token_value[1] == '?')
		return (expand_exitstatus(data->exitstatus, current));
	while ((*env)[idx])
	{
		if (!envcmp((*env)[idx], &current->token_value[1]))
		{
			if (env_has_value((*env)[idx]))
			{
				emptycheck = ft_strchr((*env)[idx], '=');
				if (emptycheck[1] != '\0')
					return (expand_to_one((*env)[idx], current));
			}
		}
		idx++;
	}
	return (expand_to_null(current));
}

t_token	*expand_tokenlst(t_token *head, char ***env, bool rd, t_metadata *data)
{
	t_token	*expandtoken;
	t_token	*expandlst;
	t_token	*itter;
	int		sep;

	itter = head;
	expandlst = NULL;
	while (itter)
	{
		if (itter->token_label == EXPAND)
		{
			expandtoken = expand_token(itter, env, data);
			token_add_back(&expandlst, expandtoken);
			if (rd && expandtoken->token_value == NULL)
			{
				head->token_label = RDIR_AMBIGUOUS;
				return (head);
			}
		}
		if (itter)
			itter = itter->next;
	}
	link_expand_tokens(&head, &expandlst);
	return (head);
}

void	expand_iolst(t_token_section **head, char ***env, t_metadata *data)
{
	t_token_section	*itter;
	t_token			*expanded;

	if (!head)
		return ;
	itter = (*head);
	while (itter)
	{
		if (itter->head && itter->head->start_pos == -1)
		{
			itter->head->token_label = RDIR_DOUBLE;
			itter = itter->next;
			continue ;
		}
		else
			expand_tokenlst(itter->head, env, true, data);
		itter = itter->next;
	}
}
