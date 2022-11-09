/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_navigation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 15:04:13 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 21:02:28 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include "../hdr/ms_enums.h"

void	init_lnav(t_line_nav *lnav, char *val)
{
	lnav->ret = val;
	lnav->i = 0;
	lnav->count = 0;
	lnav->state = STATE_START;
	lnav->prev_state = -1;
}
