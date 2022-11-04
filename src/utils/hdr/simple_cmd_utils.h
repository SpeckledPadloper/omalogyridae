/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_cmd_utils.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 15:58:47 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/04 17:41:22 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_CMD_UTILS_H
# define SIMPLE_CMD_UTILS_H

t_exec_list_sim	*simple_cmdlst_last(t_exec_list_sim	**head);
void			simple_cmd_add_back(t_exec_list_sim **head, t_exec_list_sim *new);
void			simple_cmd_clear(t_exec_list_sim **head);

#endif