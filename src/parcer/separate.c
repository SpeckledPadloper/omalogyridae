/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   separate.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 18:02:50 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/22 18:19:08 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../hdr/structs.h"
#include "hdr/parcer.h"
#include "../lexer/hdr/lexer.h"
#include "../utils/hdr/token_utils.h"

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

int	set_state_cio(t_token *temp)
{
	if (temp->token_label == LESS || temp->token_label == LESS)
		return (STATE_RDIRIN);
	else if (temp->token_label == GREAT || temp->token_label == GREATGREAT)
		return (STATE_RDIROUT);
	else
		return (STATE_CMD);
}

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

int	set_separation_limit(t_token *temp)
{
	int	separation_limit;

	separation_limit = 2;
	printf("separation_limit = %d\n", separation_limit);
	if (temp->token_label == SINGLE_QUOTE || temp->token_label == DOUBLE_QUOTE)
		separation_limit++;
	if (temp->next && (temp->next->token_label == SINGLE_QUOTE \
		|| temp->next->token_label == DOUBLE_QUOTE))
		separation_limit++;
	printf("separation_limit = %d\n", separation_limit);
	return (separation_limit);
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
	*temp = (*temp)->next;
	if ((*temp)->next)
		sep = set_separation_limit(*temp);
	while ((*temp)->next && \
		((*temp)->next->token_label >= PIPE && \
		((*temp)->next->start_pos - (*temp)->end_pos) < sep))
	{
		printf("start minus end = %d\n", ((*temp)->next->start_pos) - (*temp)->end_pos);
		*temp = (*temp)->next;
		sep = set_separation_limit(*temp);
	}
	temp2 = *temp;
	*temp = (*temp)->next;
	if (*temp == NULL)
		return (STATE_CMD);
	temp2->next = NULL;
	return (set_state_cio(*temp));
}

void	test_split_cmd_rdir(t_split_cmd_rdir *split)
{
	printf("\tCOMMAND LIST:\n");
	test_lex(split->cmd_head);
	printf("\n\n\tREDIRECT IN LIST:\n");
	test_lex(split->in_head);
	printf("\n\n\tREDIRECT OUT LIST:\n");
	test_lex(split->out_head);
}

void	split_cmd_rdir(t_token_section *current)
{
	t_token				*temp;
	t_split_cmd_rdir	*split;
	int					state;

	split = malloc(sizeof(t_split_cmd_rdir));
	split->cmd_head = NULL;
	split->in_head = NULL;
	split->out_head = NULL;
	temp = current->head;
	state = set_state_cio(temp);
	while (temp)
	{
		printf("state = %d\n", state);
		if (state == STATE_RDIRIN)
			state = add_redir_list(&split->in_head, &temp);
		else if (state == STATE_RDIROUT)
			state = add_redir_list(&split->out_head, &temp);
		else
			state = add_command_list(&split->cmd_head, &temp);
	}
	test_split_cmd_rdir(split);
}
