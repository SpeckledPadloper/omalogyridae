#include "executer.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>

#include <errno.h>



/*------------------------- cmd list simultion ---------------------------*/

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

t_file	*list_file_last(t_file *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_exec_list_sim *new_sim_node(char **path, int index, t_file *in, t_file *out)
{
	t_exec_list_sim *new;

	new = (t_exec_list_sim *)malloc(sizeof(t_exec_list_sim));
	new->cmd = path;
	new->index = index;
	new->infile_list = in;
	new->outfile_list = out;
	new->heredoc_pipe[0] = 0;
	new->heredoc_pipe[1] = 0;
	new->next = NULL;
	return (new);
}

t_file	*new_list_node(char *filename, t_open_modes mode)
{
	t_file *new;

	new = (t_file *)malloc(sizeof(t_file));
	new->filename = filename;
	new->mode = mode;
	new->next = NULL;
	return (new);
}

void make_execlist_sim(t_exec_list_sim **head, char **path, t_file *in, t_file *out)
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

void make_file_list(t_file **head, char *filename, t_open_modes mode)
{
	t_file *node;

	if (!head)
		return ;
	node = new_list_node(filename, mode);
	if (!*head)
		*head = node;
	else
		list_file_last(*head)->next = node;
}

int main(int ac, char **av, char **envp)
{

	/* init cmd_list */

	t_exec_list_sim *head = NULL;
	t_exec_list_sim *itter = NULL;

	t_file *head_in = NULL;
	t_file *head_out = NULL;
	t_file *head_neutral = NULL;
	t_file *head_outtwo = NULL;

	make_file_list(&head_neutral, "lim", LESSLESS);
	make_file_list(&head_neutral, "LIM", LESSLESS);
	make_file_list(&head_neutral, "a", LESS);

	make_file_list(&head_in, "a", LESS);
	//make_file_list(&head_in, "b", LESS);


	make_file_list(&head_out, "out_noright", GREAT);
	make_file_list(&head_outtwo, "d_out", GREAT);
	//make_file_list(&head_outtwo, "e_append", GREATGREAT);


	char *test_path1[] = {"env", NULL};
	char *test_path2[] = {"cat", "-e", NULL};
	char *test_path3[] = {"cat", "-e", NULL};
	char *test_path4[] = {"cat", "-e", NULL};
	char *test_path5[] = {"cat", "-e", NULL};
	make_execlist_sim(&head, test_path1, NULL, NULL);
	make_execlist_sim(&head, test_path2, NULL, NULL);
	make_execlist_sim(&head, test_path3, NULL, NULL);
	make_execlist_sim(&head, test_path4, NULL, NULL);
	make_execlist_sim(&head, test_path5, NULL, NULL);

	/* init padloper_envp 
		* copy environment
		* update shelllevel  */




	/* init meta data struct */
	t_fd_list	fd_list;
	ft_bzero(&fd_list, sizeof(t_fd_list));
	t_metadata meta_data;
	ft_bzero(&meta_data, sizeof(t_metadata));
	meta_data.padloper_envp = new_padloper_envp(envp);
	meta_data.fd_list = &fd_list;
	meta_data.cmd_count = ft_sim_lstsize(head);
	set_buildin_array(&meta_data);

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