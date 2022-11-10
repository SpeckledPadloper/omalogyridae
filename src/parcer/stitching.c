/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stitching.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 14:49:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 17:02:00 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include "../utils/hdr/token_utils.h"

#include <stdio.h>

static void	carryover_lapoi(t_token *source, t_token *dest)
{
	if (!source || !dest)
		return ;
	dest->token_label = source->token_label;
	dest->start_pos = source->start_pos;
	dest->i = source->i;
}

static void	stitch_token_value(char **stitched, char **temp, char *catval)
{
	if (temp)
		(*stitched) = ft_strjoin(*temp, catval);
	else
		(*stitched) = ft_strjoin("\0", catval);
	if (!(*stitched))
		exit(EXIT_FAILURE);
	if (*temp)
		free(*temp);
	*temp = *stitched;
}

static void	stitch_tokens(t_token **current)
{
	t_token			*temp;
	char			*stitched_value;
	char			*temp_str;

	temp_str = NULL;
	if ((*current)->token_value)
	{
		stitched_value = ft_strdup((*current)->token_value);
		temp_str = stitched_value;
		if (!stitched_value)
			exit(EXIT_FAILURE);
		temp = (*current)->next;
	}
	else
	{
		stitched_value = NULL;
		temp_str = NULL;
		temp = *current;
	}
	while (temp)
	{
		if (temp->token_value)
		{
			printf("stitch_tokens: %s\n", temp->token_value);
			stitch_token_value(&stitched_value, &temp_str, temp->token_value);
		}
		temp = temp->next;
	}
	temp = exp_new_token(stitched_value);
	carryover_lapoi(*current, temp);
	tokenlst_clear(current);
	(*current) = temp;
}

void	stitch_section(t_token_section **current)
{
	t_token_section	*temp;

	temp = *current;
	while (temp)
	{
		stitch_tokens(&temp->head);
		temp = temp->next;
	}
}

void	stitch(t_split_cmd_rdir **current)
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
