/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/12 16:23:16 by lwiedijk      ########   odam.nl         */
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

char	*get_error_string(char *errno_string, int errnocopy)
{
	if (errnocopy == EMPTY)
		errno_string = "something is wrong";
	else if (errnocopy == CNF)
		errno_string = "command not found";
	else if (errnocopy == AR)
		errno_string = "ambiguous redirect";
	else if (errnocopy == IS_DIR)
		errno_string = "is a directory";
	else if (errnocopy == NOT_VALID)
		errno_string = "': not a valid identifier\n";
	else if (errnocopy == TOO_MANY)
		errno_string = "minishell: exit: too many arguments\n";
	else if (errnocopy == NOT_NUMERIC)
		errno_string = ": numeric argument required\n";
	else if (errnocopy == NOT_SUPPORTED)
		errno_string = ": options not supported\n";
	return (errno_string);
}

void	print_error_exit(char *errorobject, int errnocopy, int exitcode)
{
	char	*print;
	char	*errno_string;

	print = NULL;
	errno_string = strerror(errnocopy);
	if (errnocopy <= 0)
		errno_string = get_error_string(errno_string, errnocopy);
	print = ft_strjoin("minishell: ", errorobject);
	print = ft_strjoin_free(print, ": ");
	print = ft_strjoin_free(print, errno_string);
	print = ft_strjoin_free(print, "\n");
	if (!print)
	{
		write(STDERR_FILENO, "malloc fail in error\n", 21);
		exit(EXIT_FAILURE);
	}
	write(STDERR_FILENO, print, ft_strlen(print));
	free(print);
	// make function to free all before quit, parent quit at fatal error? 
	if (exitcode)
		exit(exitcode);
}
