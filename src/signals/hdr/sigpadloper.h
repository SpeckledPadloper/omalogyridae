/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sigpadloper.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 13:59:04 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/04 16:22:11 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGPADLOPER_H
# define SIGPADLOPER_H
# include "../../hdr/structs.h"

typedef enum e_process_state
{
	PROC_PARNT = 1,
	PROC_CHLD = 2,
	PROC_HDOC = 3,
	WPID_LOOP = 4,
}	t_process_state;

void	change_tcattr(int state);
void	sig_setup(int state);
int		sig_exit(int status);

#endif