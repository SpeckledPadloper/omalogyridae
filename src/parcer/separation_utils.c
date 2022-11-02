/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   separation_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 19:38:46 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/02 20:05:44 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../hdr/structs.h"
#include "hdr/parcer.h"
#include "../lexer/hdr/lexer.h"
#include "../utils/hdr/token_utils.h"

int	set_state_cio(t_token *temp)
{
	if (temp == NULL)
		return (STATE_CMD);
	if (temp->token_label == LESS || temp->token_label == LESSLESS)
		return (STATE_RDIRIN);
	else if (temp->token_label == GREAT || temp->token_label == GREATGREAT)
		return (STATE_RDIROUT);
	else
		return (STATE_CMD);
}

int	set_separation_limit(t_token *temp)
{
	int	separation_limit;

	if (temp == NULL || temp->next == NULL)
		return (0);
	separation_limit = 1;
	if (temp->token_label == SINGLE_QUOTE || temp->token_label == DOUBLE_QUOTE)
		separation_limit++;
	if (temp->next && (temp->next->token_label == SINGLE_QUOTE \
		|| temp->next->token_label == DOUBLE_QUOTE))
		separation_limit++;
	return (separation_limit);
}

bool	set_quote_state(bool dq, t_token *temp, int sep)
{
	if (temp == NULL)
		return (false);
	if (dq == false && temp->token_label == DOUBLE_QUOTE)
		return (true);
	else if (dq == true && temp->token_label != DOUBLE_QUOTE)
	{
		if (temp->next && sep < (temp->next->start_pos - temp->end_pos) + 1)
			return (false);
	}
	return (dq);
}

void	free_cmd_rdir(t_split_cmd_rdir	**split)
{
	if (!split || !(*split))
		return ;
	clear_section(&(*split)->in_head);
	clear_section(&(*split)->out_head);
	free(*split);
}
