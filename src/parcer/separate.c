/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   separate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:02:50 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/26 19:45:02 by mteerlin      ########   odam.nl         */
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

#include "../tests/tests.h"

/**
 * separation == 2;
 *
 * if (token is LESS or LESSLESS) 
 * 		if (label next == quote label)
 * 			separation++
 * 		if (label == quote label)
 * 			separation++;
 * 		while (token end a - token start b < separation)
 * 			consider token to be part of this list
 * 			separation == 2;
 * 			if (label next == quote label)
 * 				separation++
 * 			if (label == quote label)
 * 				separation++;
 * 
 * if (token is GREAT or GREATGREAT)
 * 		same as LESS or LESSLESS
 * 
 * if (token is anything else)
 * 		add tokens to the set until redirect character is found
 */

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
	if ((*temp)->next)
		sep = set_separation_limit(*temp);
	while ((*temp)->next && \
		((*temp)->next->token_label >= PIPE && \
		((*temp)->next->start_pos - (*temp)->end_pos) <= sep))
	{
		*temp = (*temp)->next;
		sep = set_separation_limit(*temp);
	}
	temp2 = *temp;
	*temp = (*temp)->next;
	temp2->next = NULL;
	return (set_state_cio(*temp));
}

t_split_cmd_rdir	*split_cmd_rdir(t_token_section *current)
{
	t_token				*temp;
	t_token				*commands;
	t_token				*rdir_in;
	t_token				*rdir_out;
	t_split_cmd_rdir	*split;
	int					state;

	split = malloc(sizeof(t_split_cmd_rdir));
	split->cmd_head = NULL;
	commands = NULL;
	rdir_in = NULL;
	rdir_out = NULL;
	temp = current->head;
	state = set_state_cio(temp);
	while (temp)
	{
		if (state == STATE_RDIRIN)
			state = add_redir_list(&rdir_in, &temp);
		else if (state == STATE_RDIROUT)
			state = add_redir_list(&rdir_out, &temp);
		else
			state = add_command_list(&commands, &temp);
	}
	split->cmd_head = cmdlst_split(&commands);
	split->in_head = rdirlst_split(&rdir_in, LESS, LESSLESS);
	split->out_head = rdirlst_split(&rdir_out, GREAT, GREATGREAT);
	return (split);
}
