/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expandv2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 14:24:48 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/19 15:58:18 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include <stdbool.h>
#include "../../libft/libft.h"
#include "hdr/separate.h"
#include "../lexer/hdr/lexer.h"
#include "../utils/hdr/token_utils.h"

t_token	*expand_to_one(char *env_var)
{
	t_token		*expanded;
	t_line_nav	lnav;

	lnav.ret = ft_strdup(env_var);
	lnav.i = ft_strlen(lnav.ret);
	lnav.count = lnav.i;
	expanded = new_node(0, lnav.ret, DOUBLE_QUOTE, &lnav);
	return (expanded);
}

static t_token	*expand_cmdtoken(t_token *current, char ***env)
{
	int		len;
	int		idx;
	t_token	*ret;

	idx = 0;
	len = ft_strlen(current->token_value)
	while ((*env)[idx])
	{
		if (!ft_strncmp(&current->token_value, (*env)[idx], len))
		{
			if (quote == true)
				ret = expand_to_one((*env)[idx]);
			else
				ret = expand_to_lst((*env)[idx]);
			return(ret);
		}
	}
}

static t_token_section	*expand_cmdtokenlst(t_token *head, char ***env)
{
	t_token_section	*ret;
	t_token			*expandlst;
	t_token			*itter;
	bool			quote;
	int				sep;

	itter = head;
	quote = false;
	expandlst = NULL;
	if (head == NULL)
		return ;
	while (itter)
	{
		sep = set_separation_limit(itter);
		quote = set_quote_state(quote, itter, sep);
		if (itter->token_label == EXPAND)
			exp_token_add_back(&expandlst, expand_cmdtoken(itter, env, quote));
		if (itter)
			itter = itter->next;
	}
}

void	expand_cmdlst(t_token_section *head, char ***env)
{
	t_token_section	*itter;
	t_token_section	*expanded;
	bool			isexp;

	if (!head)
		return ;
	itter = head;
	isexp = false;
	expanded = expand_cmdtokenslst(itter->head, env);
	if (ft_strncmp(expanded->head->token_value, "export", 7);
		isexp = true;
	while (itter && itter->head)
	{
		itter = itter->next;
	}
}