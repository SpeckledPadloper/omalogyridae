/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stx_error.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 19:37:01 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/18 20:17:14 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../libft/libft.h"
#include "../hdr/structs.h"

void	syntax_error(char *token)
{
	write(2, SHLNAME, ft_strlen(SHLNAME));
	write(2, ": syntax error near unexpected token '", 38);
	ft_putstr_fd(token, 2);
	write(2, "'\n", 2);
}
