/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/01 14:33:10 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/10 14:01:32 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include "../utils/hdr/token_utils.h"
#include <stdlib.h>
#include "../utils/hdr/filelst_utils.h"
#include "../utils/hdr/simple_cmd_utils.h"
#include "../../libft/libft.h"

static void	set_tokval_to_array(char **ret, int *idx, char *value)
{
	ret[*idx] = ft_strdup(value);
	if (ret[*idx] == NULL)
		exit(EXIT_FAILURE);
	(*idx)++;
}

static char	**set_commands(t_token *head)
{
	char			**ret;
	int				idx;
	t_token			*temp;

	if (head == NULL)
		return (NULL);
	idx = tokenlst_len(head);
	ret = malloc(sizeof(char *) * (idx + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	temp = head;
	idx = 0;
	while (temp)
	{
		if (temp->token_value)
			set_tokval_to_array(ret, &idx, temp->token_value);
		temp = temp->next;
	}
	tokenlst_clear(&head);
	ret[idx] = NULL;
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
		temp->head->token_value = NULL;
		temp = temp->next;
	}
	tokenlst_clear(&head->head);
	return (ret);
}

t_simple_cmd	*set_simple_command(t_split_cmd_rdir *current)
{
	t_simple_cmd	*simple_cmd;
	static int		index = 0;

	if (current == NULL)
		return (NULL);
	simple_cmd = malloc(sizeof(t_simple_cmd));
	if (!simple_cmd)
		exit(EXIT_FAILURE);
	simple_cmd->cmd = set_commands(current->cmd_head);
	simple_cmd->infile_list = set_redir(current->in_head);
	clear_section(&current->in_head);
	simple_cmd->outfile_list = set_redir(current->out_head);
	clear_section(&current->out_head);
	simple_cmd->next = NULL;
	simple_cmd->index = index;
	simple_cmd->heredoc_pipe[0] = 0;
	index++;
	return (simple_cmd);
}
