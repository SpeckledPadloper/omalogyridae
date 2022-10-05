/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/05 15:46:56 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
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
	char	buffer[CNF_BUF_SIZE];

	print = NULL;
	if (!errnocopy)
	{
		ft_strlcpy(buffer, "command not found", CNF_BUF_SIZE);
		errno_string = buffer;
	}
	else
		errno_string = strerror(errnocopy);
	if (errorobject)
	{
		print = ft_strjoin("minishell: ", errorobject);
		print = ft_strjoin_free(print, ": ");
	}
	print = ft_strjoin_free(print, errno_string);
	print = ft_strjoin_free(print, "\n");
	write(STDERR_FILENO, print, ft_strlen(print));
	free(print);
	if (exitcode)
		exit(exitcode);
}
