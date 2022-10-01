/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filelst_utils.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 15:39:15 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/01 15:41:41 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILELST_UTILS_H
# define FILELST_UTILS_H

t_file	*filelst_new(char *content, int flag);
t_file	*filelst_last(t_file *head);
void	filelst_add_back(t_file **head, t_file *new);

#endif
