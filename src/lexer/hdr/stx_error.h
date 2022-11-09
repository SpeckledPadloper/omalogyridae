/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stx_error.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 19:39:40 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/09 20:39:02 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STX_ERRORS_H
# define STX_ERRORS_H
# include "../../hdr/structs.h"
# include <stdbool.h>

bool	syntax_error(char *token, t_token **head, int *exitstatus);
bool	found_syntax_start(char *val, t_token **head, int *exitstatus);
bool	found_syntax_middle(char *val, t_token *node, \
							t_token **head, int *exitstatus);

#endif