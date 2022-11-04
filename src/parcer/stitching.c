/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stitching.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 14:49:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/03 16:20:12 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include <unistd.h>
#include "../../libft/libft.h"
#include <stdlib.h>
#include "../utils/hdr/token_utils.h"

#include <stdio.h>
#include "../tests/tests.h"

bool	is_ambiguous_rdir(t_token *current)
{
	t_token	*temp;

	temp = current;
	while (temp)
	{
		if (temp->token_label == RDIR_AMBIGUOUS)
			return (true);
		temp = temp->next;
	}
	return (false);
}

static void	stitch_tokens(t_token **current)
{
	t_token			*temp;
	char			*stitched_value;
	char			*temp_str;

	temp = *current;
	temp_str = malloc(sizeof(char));
	temp_str[0] = '\0';
	if (!temp_str)
		exit(EXIT_FAILURE);
	while (temp)
	{
		if (temp->token_value)
		{
			stitched_value = ft_strjoin(temp_str, temp->token_value);
			free(temp_str);
			temp_str = stitched_value;
		}
		temp = temp->next;
	}
	temp = exp_new_token(stitched_value);
	if ((*current))
	{
		temp->token_label = (*current)->token_label;
		temp->start_pos = (*current)->start_pos;
		temp->i = (*current)->i;
	}
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
			//test_lex(itter->head);
			token_add_back(&cmd_new, itter->head);
			itter = itter->next;
		}
		free(cmd_split);
		(*current)->cmd_head = cmd_new;
	}
	if ((*current)->in_head)
		stitch_section(&(*current)->in_head);
	if ((*current)->out_head)
		stitch_section(&(*current)->out_head);
}
