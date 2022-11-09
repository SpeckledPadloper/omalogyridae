/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/09 21:06:11 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdbool.h>
# include "../../hdr/structs.h"
# include "../../hdr/ms_enums.h"
# include "../../utils/hdr/token_utils.h"

bool		is_special_char(char current);
bool		is_end_of_input(char current_plus_one);
bool		is_token_separator(char current);
bool		is_literal(char current);
bool		is_closing_char(char current, int token_label);

char		*do_special_char(t_line_nav *lnav);

#endif