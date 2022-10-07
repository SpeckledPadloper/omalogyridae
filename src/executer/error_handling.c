/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/07 08:59:06 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

void	print_error_exit(char *errorobject, int errnocopy, int exitcode)
{
	char	*print;
	char	*errno_string;

	print = NULL;
	if (errnocopy == CNF)
		errno_string = "command not found";
	else if (errnocopy == AR)
		errno_string = "ambiguous redirect";
	else
		errno_string = strerror(errnocopy);
	print = ft_strjoin("minishell: ", errorobject);
	print = ft_strjoin_free(print, ": ");
	print = ft_strjoin_free(print, errno_string);
	print = ft_strjoin_free(print, "\n");
	write(STDERR_FILENO, print, ft_strlen(print));
	free(print);
	if (exitcode)
		exit(exitcode);
}
