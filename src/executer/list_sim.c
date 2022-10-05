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







	/* init meta data struct */
	t_fd_list	fd_list;
	ft_bzero(&fd_list, sizeof(t_fd_list));
	t_metadata meta_data;
	ft_bzero(&meta_data, sizeof(t_metadata));
	meta_data.padloper_envp = new_padloper_envp(envp, &meta_data.envp_size);
	meta_data.fd_list = &fd_list;
	meta_data.cmd_count = ft_sim_lstsize(head);
	set_buildin_array(&meta_data);

	printf("envp_size = %d\n", meta_data.envp_size);

	//itter = head;
	//while (itter)
	//{
	//	printf("nodes are: index: %d, path: %s flag: %s infile: %s outfile: %s\n", itter->index, itter->cmd[0], itter->cmd[1], itter->path_fd_in, itter->path_fd_out);
	//	itter = itter->next;
	//}

	executer(&meta_data, head);
	//system("lsof -c minishell");

	return(meta_data.exitstatus);

}