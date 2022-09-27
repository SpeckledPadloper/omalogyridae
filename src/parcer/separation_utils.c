/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   separation_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 19:38:46 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/27 18:44:54 by mteerlin      ########   odam.nl         */
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

bool	set_dquote_flag(bool dq, t_token *temp, int sep)
{
	if (dq == false && temp->token_label == DOUBLE_QUOTE)
		return (true);
	else if (dq == true && temp->token_label != DOUBLE_QUOTE && sep > 1)
		return (false);
	return (dq);
}
