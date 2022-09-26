/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 15:28:53 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/26 18:50:27 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include <stdio.h>
#include "../../libft/libft.h"
#include "../utils/hdr/token_utils.h"

void	test_lex(t_token *head)
{
	t_token		*itter;

	if (!head)
		return ;
	itter = head;
	printf("before test_lex loop\n");
	while (itter)
	{
		printf("in test_lex loop\n");
		printf("token = %s\t| token_label = %d\t| token_index = %d\t| token_start = %d\t| token_end = %d\t| token_len = %zu\n", itter->token_value, itter->token_label, itter->i, itter->start_pos, itter->end_pos, ft_strlen(itter->token_value));
		itter = itter->next;
	}
	printf("after test_lex loop\n");
}

void	test_split(t_token_section *first)
{
	t_token_section	*itter;
	int				i;

	if (!first)
		return ;
	itter = first;
	i = 1;
	while (itter)
	{
		printf("SECTION: %d\n\n", i);
		test_lex(itter->head);
		printf("\n\n");
		i++;
		itter = itter->next;
	}
}

void	test_split_cmd_rdir(t_split_cmd_rdir *split)
{
	printf("\tCOMMAND LIST:\n");
	test_lex(split->cmd_head);
	printf("\n\n\tREDIRECT IN LIST:\n");
	test_split(split->in_head);
	printf("\n\n\tREDIRECT OUT LIST:\n\n\n");
	test_split(split->out_head);
}
