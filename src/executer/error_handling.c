/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/11/10 14:29:43 by lwiedijk      ########   odam.nl         */
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
	if (errnocopy > 0)
		errno_string = strerror(errnocopy);
	else if (errnocopy == EMPTY)
		errno_string = "something is wrong";
	else if (errnocopy == CNF)
		errno_string = "command not found";
	else if (errnocopy == AR)
		errno_string = "ambiguous redirect";
	else if (errnocopy == IS_DIR)
		errno_string = "is a directory";
	else if (errnocopy == NOT_VALID)
		errno_string = "': not a valid identifier";
	else if (errnocopy == TOO_MANY)
		errno_string = "minishell: exit: too many arguments";
	else if (errnocopy == NOT_NUMERIC)
		errno_string = ": numeric argument required";
	else if (errnocopy == NOT_SUPPORTED)
		errno_string = ": options not supported";
	else if (errnocopy == NOT_SUPPORTED_BOTH)
		errno_string = ": options or arguments not supported";
	else if (errnocopy == NO_PATH)
		errno_string = ": path as argument is required";
	return (errno_string);
}

static void	fatal_error(void)
{
	write(STDERR_FILENO, "SpeckledPadloper: ft_strjoin: Out of memory\n", 37);
	exit(EXIT_FAILURE);
}

void	error_too_many_arg(t_metadata *data)
{
	char	*message;

	data->exitstatus = EXIT_FAILURE;
	message = "SpeckledPadloper: exit: too many arguments\n";
	write(STDERR_FILENO, message, ft_strlen(message));
	return ;
}

void	builtin_error(char *program, char *object, int errnum, t_metadata *data)
{
	char	*print;
	char	*message;

	data->exitstatus = EXIT_FAILURE;
	message = NULL;
	message = get_error_string(message, errnum);
	print = NULL;
	print = ft_strjoin(SHLERR, program);
	if (!print)
		fatal_error();
	print = ft_strjoin_free(print, object);
	if (!print)
		fatal_error();
	if (errnum > 0 || errnum == AR)
		print = ft_strjoin_free(print, ": ");
	print = ft_strjoin_free(print, message);
	if (!print)
		fatal_error();
	print = ft_strjoin_free(print, "\n");
	if (!print)
		fatal_error();
	write(STDERR_FILENO, print, ft_strlen(print));
	free(print);
}

void	print_error_exit(char *errorobject, int errnocopy, int exitcode)
{
	char	*print;
	char	*errno_string;

	print = NULL;
	errno_string = NULL;
	errno_string = get_error_string(errno_string, errnocopy);
	print = ft_strjoin(SHLERR, errorobject);
	if (!print)
		fatal_error();
	print = ft_strjoin_free(print, ": ");
	if (!print)
		fatal_error();
	print = ft_strjoin_free(print, errno_string);
	if (!print)
		fatal_error();
	print = ft_strjoin_free(print, "\n");
	if (!print)
		fatal_error();
	write(STDERR_FILENO, print, ft_strlen(print));
	free(print);
	exit(exitcode);
}
