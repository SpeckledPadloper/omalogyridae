/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stitching.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 14:49:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 19:10:24 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include "../utils/hdr/token_utils.h"

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
	if (*temp)
		(*stitched) = ft_strjoin(*temp, catval);
	else
		(*stitched) = ft_strjoin("\0", catval);
	if (!(*stitched))
		exit(EXIT_FAILURE);
	if (*temp)
		free(*temp);
	*temp = *stitched;
}

static t_token	*stitch_head_value(char **stitch, char **t_str, t_token **head)
{
	t_token	*temp;

	if ((*head)->token_value)
	{
		*stitch = ft_strdup((*head)->token_value);
		*t_str = *stitch;
		if (!(*stitch))
			exit(EXIT_FAILURE);
		temp = (*head)->next;
	}
	else
		temp = *head;
	return (temp);
}

static void	stitch_tokens(t_token **current)
{
	t_token			*temp;
	char			*stitched_value;
	char			*temp_str;

	temp_str = NULL;
	stitched_value = NULL;
	temp = stitch_head_value(&stitched_value, &temp_str, current);
	while (temp)
	{
		if (temp->token_value)
			stitch_token_value(&stitched_value, &temp_str, temp->token_value);
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
