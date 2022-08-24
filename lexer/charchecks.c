/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   charchecks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/24 15:12:42 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/08/24 15:30:24 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h> //path max
#include <unistd.h> //getcwd 

#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <string.h>
#include <stdbool.h>
#include "libft.h"
#include "lexer.h"

#define KNRM  "\e[0m"
#define KRED  "\e[1;31m"

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
		current == '|')
		return (true);
	return (false);
}

bool	is_literal(char current)
{
	if (current == '"' || current == 39) 
		return (true);
	return (false);
}

bool	is_closing_char(char current, int token_label)
{
	if (token_label == DOUBLE_QUOTE && current == '"')
		return (true);
	if (token_label == SINGLE_QUOTE && current == '\'')
		return (true);
	else
		return (false);
}