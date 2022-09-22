/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 15:29:23 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/20 15:39:45 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H
# include "../hdr/structs.h"

void	test_lex(t_token *head);
void	test_split(t_token_section *first);

#endif