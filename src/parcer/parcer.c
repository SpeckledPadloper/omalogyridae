/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:44:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/05 16:49:03 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/parcer.h"
#include "../utils/hdr/token_utils.h"
#include "../lexer/hdr/charchecks.h"
#include "../../libft/libft.h"
#include "hdr/separate.h"
#include <stdbool.h>
#include "hdr/expand.h"
#include "../utils/hdr/simple_cmd_utils.h"

#include "../tests/tests.h" //for testing, remove before handin
#include <stdio.h>
#include <unistd.h>

void	expand_variables(t_split_cmd_rdir *head, char ***env)
{
	expand_section(&head->cmd_head, env, false);
	expand_section(&head->in_head, env, true);
	expand_section(&head->out_head, env, true);
}

t_exec_list_sim	*parce(t_token *head, char ***env)
{
	t_token_section		*first;
	t_token_section		*temp;
	t_split_cmd_rdir	*split;
	t_exec_list_sim		*simple_cmd;

	first = tokenlst_split(&head);
	//test_split(first);
	//printf("\n");
	temp = first;
	simple_cmd = NULL;
	while (temp)
	{
		split = split_cmd_rdir(temp);
		//test_split_cmd_rdir(split);
		expand_variables(split, env);
		//test_split_cmd_rdir(split);
		stitch(&split);
		//test_split_cmd_rdir(split);
		simple_cmd_add_back(&simple_cmd, set_simple_command(split));
		//free_cmd_rdir(&split);
		test_simple_command(simple_cmd);
		temp = temp->next;
	}
	return (simple_cmd);
}
