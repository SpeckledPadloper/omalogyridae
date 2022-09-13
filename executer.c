#include "executer.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

/*------------------------- utils ---------------------------*/

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

/*------------------------- basic errors need fix ---------------------------*/

void	error_message_and_exit(void)
{
	perror("minishell");
	exit(EXIT_FAILURE);
}

void	error_message_and_continue(char *error_object)
{
	if (write(STDERR_FILENO, "minishell: ", 11) == -1)
		error_message_and_exit();
	perror(error_object);
}

void	close_and_check(int fd)
{
	int	fail_check;

	fail_check = close(fd);
	if (fail_check == -1)
		error_message_and_continue("fd");
}

/*------------------------- basic executer ---------------------------*/

void	execute_cmd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char	*path;

	path = NULL;
	path = cmd_list->cmd[0];
	//open_nessesary_fd();
	//redirect_fd(cmd_list->fd_list, data);
	//close_unused_fd(cmd_list->fd_list, data);
	//path = path_parser(cmd_vectors[data->child_count][0], envp); // will be path checker, is handy in child
	execve(path, cmd_list->cmd, data->envp);
	error_message_and_exit();
}

static void	fork_processes(t_metadata *data, t_exec_list_sim *cmd_list)
{
	while (data->child_count < data->cmd_count)
	{
		cmd_list->fd_list.pipe_to_read = cmd_list->fd_list.pipe[0];
		if ((data->child_count + 1) != data->cmd_count)
		{
			if (pipe(cmd_list->fd_list.pipe) == -1)
				error_message_and_exit();
		}
		data->lastpid = fork();
		if (data->lastpid == -1)
			error_message_and_exit();
		else if (data->lastpid == 0)
			execute_cmd(data, cmd_list);
		if ((data->child_count + 1) != data->cmd_count)
			close_and_check(cmd_list->fd_list.pipe[1]);
		if (cmd_list->fd_list.pipe_to_read != 0)
			close_and_check(cmd_list->fd_list.pipe_to_read);
		data->child_count++;
		if (cmd_list)
			cmd_list = cmd_list->next;
	}
}

void	executer(t_metadata *meta_data, t_exec_list_sim *cmd_list)
{
	int		status;
	pid_t	wp;

	fork_processes(meta_data, cmd_list);
	while (1)
	{
		wp = waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
			printf("!!!error nr [%d] print error message functie call vanuit hier\n", WEXITSTATUS(status));
		if (wp == meta_data->lastpid)
			meta_data->exitstatus = WEXITSTATUS(status);
		else if (wp == -1)
			break ;
	}
}

/*------------------------- cmd list simultion ---------------------------*/

t_exec_list_sim	*list_sim_last(t_exec_list_sim *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_exec_list_sim *new_sim_node(char **path, int index, char *in, char *out)
{
	t_exec_list_sim *new;

	new = (t_exec_list_sim *)malloc(sizeof(t_exec_list_sim));
	new->cmd = path;
	new->index = index;
	new->path_fd_in = in;
    new->path_fd_out = out;
	new->next = NULL;
	ft_bzero(&new->fd_list, sizeof(t_fd_list));
	return (new);
}

void make_execlist_sim(t_exec_list_sim **head, char **path, char *in, char *out)
{
    static int count = 0;
	t_exec_list_sim *node;

	if (!head)
		return ;
	count += 1;
	node = new_sim_node(path, count, in, out);
	if (!*head)
		*head = node;
	else
		list_sim_last(*head)->next = node;
}

int main(int ac, char **av, char **env)
{

	/* init cmd_list */

	t_exec_list_sim *head = NULL;
	t_exec_list_sim *itter = NULL;
	char **test_paths[5];

	char *test_path1[] = {"/bin/ls", "-la", NULL};
	char *test_path2[] = {"cat", "-e", NULL};
	char *test_path3[] = {"cat", "-e", NULL};
	test_paths[0] = test_path1;
	test_paths[1] = test_path2;
	test_paths[2] = test_path3;
	make_execlist_sim(&head, test_paths[0], NULL, NULL);
	make_execlist_sim(&head, test_paths[1], "infile.txt", NULL);
	make_execlist_sim(&head, test_paths[2], NULL, NULL);

	/* init mata data struct */

	t_metadata meta_data;
	ft_bzero(&meta_data, sizeof(t_metadata));
	meta_data.envp = env;
	meta_data.cmd_count = ft_sim_lstsize(head);

	itter = head;
	while (itter)
	{
		printf("nodes are: index: %d, path: %s flag: %s\n", itter->index, itter->cmd[0], itter->cmd[1]);
		itter = itter->next;
	}

	executer(&meta_data, head);

	return(meta_data.exitstatus);

	


	//for (int i = 0; i < 3; i++)
	//{
	//	make_execlist_sim(&head, test_paths[i], NULL, NULL);
	//}
	



}