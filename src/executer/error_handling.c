/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/06 15:19:23 by lwiedijk      ########   odam.nl         */
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

//char	*get_error_string(int errnocopy, char *buffer)
//{
//	if (errnocopy == CNF)
//		ft_strlcpy(buffer, "command not found", CNF_BUF_SIZE);
//	if (errnocopy == AR)
//		ft_strlcpy(ar_buffer, "ambiguous redirect", AR_BUF_SIZE);
//}

void	print_error_exit(char *errorobject, int errnocopy, int exitcode)
{
	char	*print;
	char	*errno_string;
	char	buffer[CNF_BUF_SIZE];
	char	ar_buffer[AR_BUF_SIZE];

	print = NULL;
	if (errnocopy == CNF)
	{
		ft_strlcpy(buffer, "command not found", CNF_BUF_SIZE);
		errno_string = buffer;
	}
	else if (errnocopy == AR)
	{
		ft_strlcpy(ar_buffer, "ambiguous redirect", AR_BUF_SIZE);
		errno_string = ar_buffer;
	}
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
