/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 14:33:10 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/01 20:22:08 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include <unistd.h>
#include "../utils/hdr/token_utils.h"
#include <stdlib.h>
#include "../utils/hdr/filelst_utils.h"
#include "../../libft/libft.h"

#include <stdio.h>
#include "../tests/tests.h"

static char	**set_commands(t_token_section *head)
{
	char			**ret;
	int				len;
	t_token_section	*temp;
	int				cnt;

	if (head == NULL)
		return (NULL);
	len = token_section_len(head);
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	temp = head;
	cnt = 0;
	while (temp && cnt < len)
	{
		ret[cnt] = ft_strdup(temp->head->token_value);
		cnt++;
		temp = temp->next;
	}
	ret[cnt] = NULL;
	return (ret);
}

static int	determine_file_flag(t_token	*current)
{
	int	ret;

	if (current->token_label == RDIR_AMBIGUOUS)
		ret = RDIR_AMBIGUOUS;
	else if (current->start_pos < 0)
		ret = RDIR_DOUBLE;
	else
		ret = RDIR_SINGLE;
	return (ret);
}

static t_file	*set_redir(t_token_section *head)
{
	t_file			*ret;
	t_token_section	*temp;
	int				flag;

	ret = NULL;
	temp = head;
	while (temp)
	{
		flag = determine_file_flag(temp->head);
		filelst_add_back(&ret, filelst_new(temp->head->token_value, flag));
		temp = temp->next;
	}
	return (ret);
}

t_exec_list_sim	*set_simple_command(t_split_cmd_rdir *current)
{
	t_exec_list_sim	*simple_cmd;
	static int		index = 0;

	if (current == NULL)
		return (NULL);
	simple_cmd = malloc(sizeof(t_exec_list_sim));
	if (!simple_cmd)
		exit(EXIT_FAILURE);
	simple_cmd->cmd = set_commands(current->cmd_head);
	simple_cmd->infile_list = set_redir(current->in_head);
	simple_cmd->outfile_list = set_redir(current->out_head);
	simple_cmd->next = NULL;
	simple_cmd->index = index;
	index++;
	return (simple_cmd);
}
