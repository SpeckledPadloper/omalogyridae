/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 20:12:56 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 20:20:48 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "structs.h"

int	g_exitstatus;

t_token			*lex(char *ret, int *exitstatus);
t_simple_cmd	*parce(t_token *head, char ***env, t_metadata *data);
void			executer(t_metadata *meta_data, t_simple_cmd *cmd_list);

#endif