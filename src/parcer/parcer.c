/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:44:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/03 12:28:59 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/parcer.h"
#include "../utils/hdr/token_utils.h"
#include "../lexer/hdr/charchecks.h"
#include "../../libft/libft.h"
#include "hdr/separate.h"
#include <stdbool.h>
#include "hdr/expandv2.h"
#include "../utils/hdr/simple_cmd_utils.h"
#include <stdlib.h>

#include "../tests/tests.h" //for testing, remove before handin
#include <stdio.h>
#include <unistd.h>

static void	expand_variables(t_split_cmd_rdir *head, \
							char ***env, t_metadata *data)
{
	head->cmd_head = expand_tokenlst(head->cmd_head, env, false, data);
	expand_iolst(&head->in_head, env, data);
	expand_iolst(&head->out_head, env, data);
}

t_exec_list_sim	*parce(t_token *head, char ***env, t_metadata *data)
{
	t_token_section		*first;
	t_token_section		*temp;
	t_split_cmd_rdir	*split;
	t_exec_list_sim		*simple_cmd;

	first = tokenlst_split(&head);
	// test_split(first);
	//printf("\n");
	temp = first;
	simple_cmd = NULL;
	while (temp)
	{
		split = split_cmd_rdir(temp);
		// test_split_cmd_rdir(split);
		expand_variables(split, env, data);
		// test_split_cmd_rdir(split);
		stitch(&split);
		// printf("\tpost stitch\n");
		// test_split_cmd_rdir(split);
		simple_cmd_add_back(&simple_cmd, set_simple_command(split));
		free(split);
		temp = temp->next;
	}
	printf("\n\n\n");
	test_simple_command(simple_cmd);
	printf("\n\n\n");
	return (simple_cmd);
}
