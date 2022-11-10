/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:44:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 18:04:24 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/parcer.h"
#include "../lexer/hdr/charchecks.h"
#include "../../libft/libft.h"
#include "hdr/separate.h"
#include <stdbool.h>
#include "hdr/expand.h"
#include "../utils/hdr/simple_cmd_utils.h"
#include <stdlib.h>

static void	expand_variables(t_split_cmd_rdir *head, \
							char ***env, t_metadata *data)
{
	head->cmd_head = expand_tokenlst(head->cmd_head, env, false, data);
	expand_iolst(&head->in_head, env, data);
	expand_iolst(&head->out_head, env, data);
}

static void	stitch(t_split_cmd_rdir **current)
{
	t_token_section	*cmd_split;
	t_token_section	*itter;
	t_token			*cmd_new;

	cmd_new = NULL;
	cmd_split = cmdlst_split(&(*current)->cmd_head);
	if ((*current)->cmd_head)
	{
		stitch_section(&cmd_split);
		itter = cmd_split;
		while (itter)
		{
			token_add_back(&cmd_new, itter->head);
			itter = itter->next;
			free(cmd_split);
			cmd_split = itter;
		}
		(*current)->cmd_head = cmd_new;
	}
	if ((*current)->in_head)
		stitch_section(&(*current)->in_head);
	if ((*current)->out_head)
		stitch_section(&(*current)->out_head);
}

t_simple_cmd	*parce(t_token *head, char ***env, t_metadata *data)
{
	t_token_section		*first;
	t_token_section		*temp;
	t_split_cmd_rdir	*split;
	t_simple_cmd		*simple_cmd;

	first = tokenlst_split(&head);
	simple_cmd = NULL;
	while (first)
	{
		temp = first;
		split = split_cmd_rdir(first);
		first = first->next;
		free(temp);
		expand_variables(split, env, data);
		stitch(&split);
		simple_cmd_add_back(&simple_cmd, set_simple_command(split));
		free(split);
	}
	return (simple_cmd);
}
