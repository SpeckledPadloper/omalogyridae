/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   charchecks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 15:12:42 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/18 19:58:03 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../libft/libft.h"

bool	is_whitespace(char current)
{
	if (current == ' ' || (current > 8 && current < 14))
		return (true);
	return (false);
}

bool	is_special_char(char current)
{
	if (current == '<' || current == '>' || current == '|')
		return (true);
	return (false);
}

bool	is_end_of_input(char current_plus_one)
{
	if (current_plus_one == '\0')
		return (true);
	return (false);
}

bool	is_token_separator(char current)
{
	if (current == ' ' || current == '<' || current == '>' || \
		current == '|' || current == '"' || current == '\'' || \
		current == '$')
		return (true);
	return (false);
}

bool	is_redirect(char *token)
{
	if (ft_strncmp(token, "<", 2) || ft_strncmp(token, "<<", 3) || \
		ft_strncmp(token, ">", 2) || ft_strncmp(token, ">>", 3))
	{
		return (true);
	}
	return (false);
}
