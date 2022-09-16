/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   charchecks.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 12:43:25 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/14 12:44:17 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARCHECKS_H
# define CHARCHECKS_H

bool	is_whitespace(char current);
bool	is_special_char(char current);
bool	is_end_of_input(char current_plus_one);
bool	is_token_separator(char current);

#endif