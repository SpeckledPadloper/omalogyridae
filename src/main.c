/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 16:18:33 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 14:44:41 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*stdio.h required for readline.h*/
#include <stdio.h> 
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "hdr/minishell.h"
#include "../libft/libft.h"
#include "utils/hdr/simple_cmd_utils.h"

#include "signals/hdr/sigpadloper.h"

static char	*input_eof(void)
{
	char	*ret;

	ret = ft_strdup("exit");
	if (ret == NULL)
		exit(EXIT_FAILURE);
	return (ret);
}

static char	*read_input(t_metadata *data)
{
	char	*input;

	input = readline(SHLPROM);
	if (input == NULL)
		input = input_eof();
	if (input[0] != '\0')
		add_history(input);
	if (g_exitstatus)
		data->exitstatus = g_exitstatus;
	return (input);
}

static void	padloper(t_fd_list *fd_list, t_metadata *data)
{
	char			*input;
	t_token			*head;
	t_simple_cmd	*sim_cmd;
	int				status;

	status = 0;
	input = "";
	while (input != NULL)
	{
		input = read_input(data);
		head = lex(input, &data->exitstatus);
		free(input);
		if (head == NULL)
			continue ;
		sim_cmd = parce(head, &data->padloper_envp, data);
		reset_metadata(data, fd_list);
		if ((sim_cmd->cmd && !sim_cmd->cmd[0]) && \
			!sim_cmd->infile_list && !sim_cmd->outfile_list)
		{
			simple_cmd_clear(&sim_cmd);
			continue ;
		}
		executer(data, sim_cmd);
		simple_cmd_clear(&sim_cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_metadata		data;
	t_fd_list		fd_list;

	(void)argc;
	(void)argv;
	sig_setup(PROC_PARNT);
	init_metadata(&data, &fd_list, env);
	padloper(&fd_list, &data);
	return (data.exitstatus);
}
