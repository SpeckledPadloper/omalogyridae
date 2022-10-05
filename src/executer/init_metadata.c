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

int	ft_sim_lstsize(t_exec_list_sim *lst)
{
	t_exec_list_sim	*temp;
	int		count;

	temp = lst;
	count = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

void	init_metadata(t_metadata *data, t_fd_list *fd_list, char **envp)
{
	ft_bzero(fd_list, sizeof(t_fd_list));
	ft_bzero(data, sizeof(t_metadata));
	data->padloper_envp = new_padloper_envp(envp, &(data->envp_size));
	data->fd_list = fd_list;
	data->cmd_count = NULL;
	set_buildin_array(data);
}
