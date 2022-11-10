/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_cmd_utils.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 15:58:47 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 13:56:02 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_CMD_UTILS_H
# define SIMPLE_CMD_UTILS_H

int				tokenlst_len(t_token *head);
t_simple_cmd	*simple_cmdlst_last(t_simple_cmd	**head);
void			simple_cmd_add_back(t_simple_cmd **head, t_simple_cmd *new);
void			simple_cmd_clear(t_simple_cmd **head);

#endif