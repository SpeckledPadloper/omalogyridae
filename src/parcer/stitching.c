/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stitching.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 14:49:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/06 18:23:16 by mteerlin      ########   odam.nl         */
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

void	stitch_tokens(t_token_section **sect, t_token **current)
{
	t_token			*temp;
	char			*stitched_value;
	char			*temp_str;
	t_token_section	*temp_sect;

	temp = *current;
	temp_str = malloc(sizeof(char));
	temp_str[0] = '\0';
	if (!temp_str)
		exit(EXIT_FAILURE);
	while (temp)
	{
		stitched_value = ft_strjoin(temp_str, temp->token_value);
		free(temp_str);
		temp_str = stitched_value;
		printf("%d\n", temp->i);
		if (temp->next && temp->next->i == temp->i)
		{
			temp_sect = (*sect)->next;
			(*sect)->next = new_token_section(temp->next);
			temp->next = NULL;
			(*sect)->next->next = temp_sect;
		}
		temp = temp->next;
	}
	temp = exp_new_token(stitched_value);
	temp->token_label = (*current)->token_label;
	temp->start_pos = (*current)->start_pos;
	temp->i = (*current)->i;
	tokenlst_clear(current);
	(*current) = temp;
}

void	stitch_section(t_token_section **current)
{
	t_token_section	*temp;

	temp = *current;
	while (temp)
	{
		printf("%p\n", temp);
		stitch_tokens(&temp, &temp->head);
		temp = temp->next;
	}
}

void	stitch(t_split_cmd_rdir **current)
{
	if ((*current)->cmd_head)
		stitch_section(&(*current)->cmd_head);
	if ((*current)->in_head)
		stitch_section(&(*current)->in_head);
	if ((*current)->out_head)
		stitch_section(&(*current)->out_head);
}
