#include "executer.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>

#include <errno.h>

void	print_error_exit(char *errorobject, int errnocopy, int exitcode)
{
	char *print;
	char *errno_string;
	char buffer[18];

	if (errnocopy == 0)
	{
		ft_strlcpy(buffer, "command not found", 18);
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