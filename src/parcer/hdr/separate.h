/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   separate.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 19:39:12 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/26 19:40:45 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATE_H
# define SEPARATE_H
# include "../../hdr/structs.h"

int	set_state_cio(t_token *temp);
int	set_separation_limit(t_token *temp);

#endif