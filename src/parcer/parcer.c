/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:44:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/23 19:08:16 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/parcer.h"
#include "../utils/hdr/token_utils.h"
#include "../../libft/libft.h"

#include "../tests/tests.h" //for testing, remove before handin
#include <stdio.h>

void	expand_tokens(t_token **head, char ***env)
{
	t_token	*temp;
	int		cnt;
	int		len;
	bool	dquote;

	temp = *head;
	dquote = false;
	while (temp)
	{
		if (dquote == false && temp->token_label == DOUBLE_QUOTE)
			dquote = true;
		if (temp->token_label == EXPAND)
		{
			cnt = 0;
			len = ft_strlen(&temp->token_value[1]);
			while ((*env)[cnt])
			{
				if (!ft_strncmp(&temp->token_value[1], (*env)[cnt], len))
				{
					printf("%s\n", (*env)[cnt]);
					break ;
				}
				cnt++;
			}
			if ((*env)[cnt] == NULL)
				printf("%s ain't here, get fucked\n", temp->token_value);
		}
		temp = temp->next;
	}
}

void	parce(t_token *head, char ***env)
{
	t_token_section		*first;
	t_token_section		*temp;
	t_split_cmd_rdir	*split;
	//t_exec_list_sim		*start;

	first = tokenlst_split(head);
	test_split(first);
	temp = first;
	while (temp)
	{
		// here will come the code to turn each split section into the final list
		// final bits of parcing, expantion, all that.
		split = split_cmd_rdir(temp);
		test_split_cmd_rdir(split);
		expand_tokens(&split->cmd_head, env);
		temp = temp->next;
	}
}
