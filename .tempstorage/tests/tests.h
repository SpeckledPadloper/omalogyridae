/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 15:29:23 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/04 17:48:31 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H
# include "../hdr/structs.h"

void	test_lex(t_token *head);
void	test_split(t_token_section *first);
void	test_split_cmd_rdir(t_split_cmd_rdir *split);
void	test_filelst(t_file *head, bool is_infile);
void	test_simple_command(t_simple_cmd	*current);

#endif