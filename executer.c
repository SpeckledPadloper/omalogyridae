#include "executer.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>

#include <errno.h>

/*------------------------- utils ---------------------------*/


void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_3d_array(char ***cmd_array)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_array[i])
	{
		j = 0;
		while (cmd_array[i][j])
		{
			free(cmd_array[i][j]);
			j++;
		}
		free(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}



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

bool	is_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (true);
		i++;
	}
	return (false);
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

void	command_not_found(char *error_object)
{
	if (write(STDERR_FILENO, "pipex: ", 7) == -1)
		error_message_and_exit();
	if (write(STDERR_FILENO, error_object, ft_strlen(error_object)) == -1)
		error_message_and_exit();
	if (write(STDERR_FILENO, ": command not found\n", 20) == -1)
		error_message_and_exit();
	exit(127);
}

//new error handling
/*
void	fatal_memory_error(void)
{
	printf("minishell: fatal memory error occured\n");
	exit(EXIT_FAILURE);
}

void	set_error_message(t_metadata *data, char *child_errstr, int exitcode)
{
	fprintf(stderr, "strerror in set_error_massage is : [ %s ]\n", child_errstr);
	write(data->err_pipe[1], child_errstr, ft_strlen(child_errstr));
	//close(data->err_pipe[1]);
	exit(exitcode);
}

void	print_error_message(t_metadata *data)
{
	int buf_size = 4096;
	int bytes_read = 0;
	char buff[buf_size];


	bytes_read = read(data->err_pipe[0], buff, buf_size);
	printf("bytes_read = [%d]\n", bytes_read);
	write(STDERR_FILENO, buff, bytes_read);
}
*/
/*-------------------------path builder--------------------------------*/



static char	*check_path(char *cmd, char **env_path, int count)
{
	char	*path;
	int		i;
	int		is_not_executable;

	path = NULL;
	i = 0;
	while (i < count)
	{
		path = ft_strjoin("/", cmd);
		if (!path)
			error_message_and_exit();
		path = ft_strjoin_free(env_path[i], path);
		if (!path)
			error_message_and_exit();
		is_not_executable = access(path, F_OK | X_OK);
		if (is_not_executable)
		{
			free(path);
			path = NULL;
		}
		else
			break ;
		i++;
	}
	return (path);
}

static char	*check_absolute_path(t_metadata *data, char *path)
{
	int	is_not_executable;
	int	file_does_not_exist;

	if (!is_path(path))
		command_not_found(path);
	is_not_executable = access(path, F_OK | X_OK);
	if (is_not_executable)
	{
		file_does_not_exist = access(path, F_OK);
		if (file_does_not_exist)
		{
			error_message_and_continue(path); // send error enum, catch in parrent if not 0, print there
			exit(127);
			//int errnocopy;
			//errnocopy = errno;
//
			//fprintf(stderr, "errno itself is : [ %d ]\n", errnocopy);
			//fprintf(stderr, "strerror in child is : [ %s ]\n", strerror(errno));
			//set_error_message(data, strerror(errno), 127);
		}
		else
		{
			error_message_and_continue(path);
			exit(126);
		}
	}
	return (path);
}

static char	**get_env_path_array(char **envp, int *count)
{
	char	**env_path;
	char	**temp;
	int		i;

	i = 0;
	temp = NULL;
	env_path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			temp = ft_split(envp[i], '=');
			if (!temp)
				error_message_and_exit();
			env_path = ft_split_and_count(temp[1], ':', count);
			if (!env_path)
				error_message_and_exit();
			free_2d_array(temp);
			break ;
		}
		i++;
	}
	return (env_path);
}

char	*path_builder(t_metadata *data, char *cmd)//char **envp)
{
	char	*path;
	char	**env_path;
	int		count;

	count = 0;
	path = NULL;
	env_path = get_env_path_array(data->envp, &count);
	path = check_path(cmd, env_path, count);
	if (!path)
		path = check_absolute_path(data, cmd);
	return (path);
}






/*------------------------- basic executer ---------------------------*/

void	open_necessary_fd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	if (cmd_list->path_fd_in)
		data->fd_list->fd_in = open(cmd_list->path_fd_in, O_RDONLY);
	if (data->fd_list->fd_in < 0)
	{
		error_message_and_continue(cmd_list->path_fd_in);
		exit(EXIT_FAILURE);
	}
	if (cmd_list->path_fd_out)
		data->fd_list->fd_out = open(cmd_list->path_fd_out, O_CREAT | O_WRONLY | O_TRUNC, MODE_RW_R_R);
	if (data->fd_list->fd_out < 0)
	{
		error_message_and_continue(cmd_list->path_fd_out);
		exit(EXIT_FAILURE);
	}
}

static void	redirect_input(t_metadata *data, t_exec_list_sim *cmd_list)
{
	//if (data->cmd_count <= 1 && !cmd_list->path_fd_in)
	//	return ;
	if (data->cmd_count > 1 && data->child_count > 0)
	{
		if (dup2(data->fd_list->pipe_to_read, STDIN_FILENO) == -1)
			error_message_and_exit();
	}
	if (cmd_list->path_fd_in)
	{
		if (dup2(data->fd_list->fd_in, STDIN_FILENO) == -1)
			error_message_and_exit();
	}
}

static void	redirect_output(t_metadata *data, t_exec_list_sim *cmd_list)
{
	if (data->cmd_count > 1 && (data->child_count + 1) != data->cmd_count)
	{
		if (dup2(data->fd_list->pipe[1], STDOUT_FILENO) == -1)
			error_message_and_exit();
	}
	if (cmd_list->path_fd_out)
	{
		if (dup2(data->fd_list->fd_out, STDOUT_FILENO) == -1)
			error_message_and_exit();
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

	if (cmd_list->path_fd_in && data->fd_list->fd_in != -1)
		close_and_check(data->fd_list->fd_in);
	if (cmd_list->path_fd_out && data->fd_list->fd_out != -1)
		close_and_check(data->fd_list->fd_out);
	close_and_check(data->err_pipe[0]);
}

void	execute_cmd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char	*path;

	path = NULL;
	open_necessary_fd(data, cmd_list);
	redirect_input(data, cmd_list);
	redirect_output(data, cmd_list);
	path = path_builder(data, cmd_list->cmd[0]);
	close_unused_fd(data, cmd_list);
	execve(path, cmd_list->cmd, data->envp);
	printf("cmd with endex [ %d ] failed\n", cmd_list->index);
	error_message_and_exit();
}

static void	fork_processes(t_metadata *data, t_exec_list_sim *cmd_list)
{
	while (data->child_count < data->cmd_count)
	{
		pipe(data->err_pipe);
		data->fd_list->pipe_to_read = data->fd_list->pipe[0];
		if ((data->child_count + 1) != data->cmd_count) //&& cmd count is more than 1
		{
			if (pipe(data->fd_list->pipe) == -1)
				error_message_and_exit();
		}
		data->lastpid = fork();
		if (data->lastpid == -1)
			error_message_and_exit();
		else if (data->lastpid == 0)
			execute_cmd(data, cmd_list);
		if ((data->child_count + 1) != data->cmd_count)
			close_and_check(data->fd_list->pipe[1]);
		if (data->fd_list->pipe_to_read != 0)
			close_and_check(data->fd_list->pipe_to_read);
		close_and_check(data->err_pipe[1]);
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
		//system("lsof -c minishell");
		wp = waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
		{
			//printf("!!!error code: [%d] print error message functie call vanuit hier\n", WEXITSTATUS(status));
			//print_error_message(meta_data);
		}
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

	char *test_path1[] = {"ls", "-la", NULL};
	char *test_path2[] = {"kaas", "-e", NULL};
	char *test_path3[] = {"kaas", NULL};
	char *test_path4[] = {"kaas", NULL};
	char *test_path5[] = {"wc", "-l", NULL};
	test_paths[0] = test_path1;
	test_paths[1] = test_path2;
	test_paths[2] = test_path3;
	test_paths[3] = test_path4;
	test_paths[4] = test_path5;
	make_execlist_sim(&head, test_paths[0], "bestaanniet", NULL);
	make_execlist_sim(&head, test_paths[1], NULL, NULL);
	make_execlist_sim(&head, test_paths[2], NULL, NULL);
	make_execlist_sim(&head, test_paths[3], NULL, NULL);
	make_execlist_sim(&head, test_paths[4], NULL, "out_noright");

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