/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stx_error.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 19:37:01 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 19:38:03 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../libft/libft.h"
#include "../hdr/structs.h"
#include "../utils/hdr/token_utils.h"
#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>

bool	syntax_error(char *token, t_token **head, int *exitstatus)
{
	*exitstatus = 258;
	write(2, SHLNAME, ft_strlen(SHLNAME));
	write(2, ": syntax error near unexpected token '", 38);
	ft_putstr_fd(token, 2);
	write(2, "'\n", 2);
	tokenlst_clear(head);
	return (false);
}

bool	found_syntax_start(char *val, t_token **head, int *exitstatus)
{
	bool	ret;

	ret = syntax_error(val, head, exitstatus);
	free(val);
	return (ret);
}

bool	found_syntax_middle(char *val, t_token *node, \
							t_token **head, int *exitstatus)
{
	bool	ret;

	ret = syntax_error(val, head, exitstatus);
	tokenlst_clear(&node);
	return (ret);
}
