#include "lexer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int	ft_lstsize(t_exec_list_sim *lst)
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







void	pipex(t_metadata *data, t_all_fd *all_fd,
			char **envp, char ***cmd_vectors)
{
	int		status;
	pid_t	wp;

	fork_processes(data, all_fd, envp, cmd_vectors);
	while (1)
	{
		wp = waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
			printf("!!!print error message functie call vanuit hier\n");
		if (wp == data->lastpid)
			data->exitstatus = WEXITSTATUS(status);
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
	new->path = path;
	new->index = index;
	new->path_fd_in = in;
    new->path_fd_out = out;
	new->next = NULL;
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
	t_exec_list_sim *head = NULL;
	t_exec_list_sim *itter = NULL;
	char **test_paths[5];

	char *test_path1[] = {"ls", "-la"};
	char *test_path2[] = {"cat", "-e"};
	char *test_path3[] = {"cat", "-e"};
	test_paths[0] = test_path1;
	test_paths[1] = test_path2;
	test_paths[2] = test_path3;
	make_execlist_sim(&head, test_paths[0], NULL, NULL);
	make_execlist_sim(&head, test_paths[1], "infile.txt", NULL);
	make_execlist_sim(&head, test_paths[2], NULL, NULL);


	//for (int i = 0; i < 3; i++)
	//{
	//	make_execlist_sim(&head, test_paths[i], NULL, NULL);
	//}
	//itter = head;
	//while (itter)
	//{
	//	printf("nodes are: index: %d, path: %s\n", itter->index, itter->path[0]);
	//	itter = itter->next;
	//}


}