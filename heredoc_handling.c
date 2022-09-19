#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "executer.h"

static char	*get_input(char *str)
{
	write (STDOUT_FILENO, "> ", 2);
	if (get_next_line(STDIN_FILENO, &str) == -1)
		print_error_exit("malloc", errno, EXIT_FAILURE);
	return (str);
}

void	heredoc_handling(int *pipe_end, char *limiter)
{
	char	*str;
	char	*temp;

	str = NULL;
	pipe(pipe_end);
	str = get_input(str);
	while (ft_strcmp(limiter, str))
	{
		temp = ft_strjoin(str, "\n");
		if (!temp)
			print_error_exit("malloc", errno, EXIT_FAILURE);
		write (pipe_end[1], temp, ft_strlen(temp));
		free(str);
		free(temp);
		str = get_input(str);
	}
	free(str);
	close(pipe_end[1]);
}
