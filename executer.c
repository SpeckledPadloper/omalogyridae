#include "executer.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>

#include <errno.h>

/*------------------------- basic executer ---------------------------*/

void	open_necessary_fd(t_metadata *data, t_exec_list_sim *cmd_list)

/* if <<, pipe, write to pipe, if not last redirect close pipe, else set
	readend_fd to data->fd_list->pipe_to_read? change or add if() in redirect_input()  */

{
	if (cmd_list->infile_list) // dit moet dat een list loop worden tot aan einde list? meteen vanuit hier close per stuk aanroepen?
		data->fd_list->fd_in = open(cmd_list->infile_list->filename, O_RDONLY);
	if (data->fd_list->fd_in < 0)
		print_error_exit(cmd_list->infile_list->filename, errno, EXIT_FAILURE);
	if (cmd_list->outfile_list)
		data->fd_list->fd_out = open(cmd_list->outfile_list->filename, O_CREAT | O_WRONLY | O_TRUNC, MODE_RW_R_R);
	if (data->fd_list->fd_out < 0)
		print_error_exit(cmd_list->outfile_list->filename, errno, EXIT_FAILURE);
}

static void	redirect_input(t_metadata *data, t_exec_list_sim *cmd_list)
{
	//if (data->cmd_count <= 1 && !cmd_list->path_fd_in)
	//	return ;
	if (data->cmd_count > 1 && data->child_count > 0)
	{
		if (dup2(data->fd_list->pipe_to_read, STDIN_FILENO) == -1)
			print_error_exit("dup2", errno, EXIT_FAILURE);
	}
	if (cmd_list->infile_list)
	{
		if (dup2(data->fd_list->fd_in, STDIN_FILENO) == -1)
			print_error_exit("dup2", errno, EXIT_FAILURE);
	}
}

static void	redirect_output(t_metadata *data, t_exec_list_sim *cmd_list)
{
	if (data->cmd_count > 1 && (data->child_count + 1) != data->cmd_count)
	{
		if (dup2(data->fd_list->pipe[1], STDOUT_FILENO) == -1)
			print_error_exit("dup2", errno, EXIT_FAILURE);
	}
	if (cmd_list->outfile_list)
	{
		if (dup2(data->fd_list->fd_out, STDOUT_FILENO) == -1)
			print_error_exit("dup2", errno, EXIT_FAILURE);
	}
}

static void	close_unused_fd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	//fprintf(stderr, "fd_list->fd_in = [ %d ]\n", data->fd_list->fd_in);
	//system("lsof -c minishell");

	if (data->fd_list->pipe[1] && (data->child_count + 1) != data->cmd_count)
		close_and_check(data->fd_list->pipe[1]);
	if (data->fd_list->pipe[0] && (data->child_count + 1) != data->cmd_count)
		close_and_check(data->fd_list->pipe[0]);

	if (data->fd_list->pipe_to_read)
		close_and_check(data->fd_list->pipe_to_read);

	if (cmd_list->infile_list && data->fd_list->fd_in != -1)
		close_and_check(data->fd_list->fd_in);
	if (cmd_list->outfile_list && data->fd_list->fd_out != -1)
		close_and_check(data->fd_list->fd_out);
}

void	execute_cmd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char	*path;

	path = NULL;
	open_necessary_fd(data, cmd_list);
	redirect_input(data, cmd_list);
	redirect_output(data, cmd_list);
	close_unused_fd(data, cmd_list);
	path = path_builder(data, cmd_list->cmd[0]);
	execve(path, cmd_list->cmd, data->envp);
	//printf("cmd with endex [ %d ] failed\n", cmd_list->index);
	print_error_exit("execve", errno, EXIT_FAILURE);
}

static void	fork_processes(t_metadata *data, t_exec_list_sim *cmd_list)
{
	while (data->child_count < data->cmd_count)
	{
		data->fd_list->pipe_to_read = data->fd_list->pipe[0];
		if ((data->child_count + 1) != data->cmd_count) //&& cmd count is more than 1
		{
			if (pipe(data->fd_list->pipe) == -1)
				print_error_exit("pipe", errno, EXIT_FAILURE);
		}
		data->lastpid = fork();
		if (data->lastpid == -1)
			print_error_exit("fork", errno, EXIT_FAILURE);
		//execute_cmd(data, cmd_list);
		else if (data->lastpid == 0)
			execute_cmd(data, cmd_list);
		if ((data->child_count + 1) != data->cmd_count)
			close_and_check(data->fd_list->pipe[1]);
		if (data->fd_list->pipe_to_read != 0)
			close_and_check(data->fd_list->pipe_to_read);
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
		if (wp == meta_data->lastpid)
			meta_data->exitstatus = WEXITSTATUS(status);
		else if (wp == -1)
			break ;
	}
}




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

int main(int ac, char **av, char **env)
{

	/* init cmd_list */

	t_exec_list_sim *head = NULL;
	t_exec_list_sim *itter = NULL;

	t_file *head_in = NULL;
	t_file *head_out = NULL;
	t_file *head_neutral = NULL;

	make_file_list(&head_in, "a", LESS);
	make_file_list(&head_in, "b", LESS);

	make_file_list(&head_out, "out_noright", GREAT);

	char *test_path1[] = {"ls", NULL};
	char *test_path2[] = {"kaas/", "-e", NULL};
	char *test_path3[] = {"cat", "-e", NULL};
	char *test_path4[] = {"ls", NULL};
	char *test_path5[] = {"cat", "-e", NULL};
	make_execlist_sim(&head, test_path4, NULL, head_out);
	make_execlist_sim(&head, test_path2, NULL, NULL);
	make_execlist_sim(&head, test_path1, NULL, NULL);
	make_execlist_sim(&head, test_path3, head_in, NULL);
	make_execlist_sim(&head, test_path5, NULL, NULL);


	/* init mata data struct */
	t_fd_list	fd_list;
	ft_bzero(&fd_list, sizeof(t_fd_list));
	t_metadata meta_data;
	ft_bzero(&meta_data, sizeof(t_metadata));
	meta_data.envp = env;
	meta_data.fd_list = &fd_list;
	meta_data.cmd_count = ft_sim_lstsize(head);

	//itter = head;
	//while (itter)
	//{
	//	printf("nodes are: index: %d, path: %s flag: %s infile: %s outfile: %s\n", itter->index, itter->cmd[0], itter->cmd[1], itter->path_fd_in, itter->path_fd_out);
	//	itter = itter->next;
	//}

	executer(&meta_data, head);

	return(meta_data.exitstatus);

}