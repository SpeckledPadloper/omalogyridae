/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   separate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:02:50 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 14:41:45 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../hdr/structs.h"
#include "hdr/parcer.h"
#include "../lexer/hdr/lexer.h"
#include "../utils/hdr/token_utils.h"
#include "hdr/separate.h"
#include "../../libft/libft.h"

int	add_command_list(t_token **cmd, t_token **temp)
{
	t_token	*temp2;

	if (!cmd || !temp)
		return (-1);
	if (!(*cmd))
		*cmd = *temp;
	else
		tokenlst_last(*cmd)->next = *temp;
	while ((*temp)->next && (*temp)->next->token_label > PIPE)
		*temp = (*temp)->next;
	temp2 = *temp;
	*temp = (*temp)->next;
	if (*temp == NULL)
		return (STATE_CMD);
	temp2->next = NULL;
	return (set_state_cio(*temp));
}

int	add_redir_list(t_token **rdir, t_token **temp)
{
	t_token	*temp2;
	int		sep;

	if (!rdir || !temp)
		return (-1);
	if (*rdir == NULL)
		*rdir = *temp;
	else
		tokenlst_last(*rdir)->next = *temp;
	sep = 1;
	*temp = (*temp)->next;
	while ((*temp)->next && \
		((*temp)->next->token_label >= PIPE && \
		((*temp)->next->start_pos - (*temp)->end_pos) <= sep))
	{
		sep = set_separation_limit(*temp);
		*temp = (*temp)->next;
	}
	temp2 = *temp;
	*temp = (*temp)->next;
	temp2->next = NULL;
	return (set_state_cio(*temp));
}

static void	construct_rdir_io(t_token_section **rdir_io)
{
	add_section_to_list(rdir_io, NULL);
	add_section_to_list(rdir_io, NULL);
}

static void	clear_rdir_io(t_token_section **rdir_io)
{
	free((*rdir_io)->next);
	free(*rdir_io);
}

t_split_cmd_rdir	*split_cmd_rdir(t_token_section *current)
{
	t_token				*temp;
	t_token_section		*rdir_io;
	t_split_cmd_rdir	*split;
	int					state;

	split = ft_calloc(sizeof(t_split_cmd_rdir), 1);
	if (!split)
		exit(EXIT_FAILURE);
	rdir_io = NULL;
	construct_rdir_io(&rdir_io);
	temp = current->head;
	state = set_state_cio(temp);
	while (temp)
	{
		if (state == STATE_RDIRIN)
			state = add_redir_list(&rdir_io->head, &temp);
		else if (state == STATE_RDIROUT)
			state = add_redir_list(&rdir_io->next->head, &temp);
		else
			state = add_command_list(&split->cmd_head, &temp);
	}
	split->in_head = rdirlst_split(&rdir_io->head, LESS, LESSLESS);
	split->out_head = rdirlst_split(&rdir_io->next->head, GREAT, 3);
	clear_rdir_io(&rdir_io);
	return (split);
}
