/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 15:28:53 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/11/04 17:48:32 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/structs.h"
#include <stdio.h>
#include "../../libft/libft.h"
#include "../utils/hdr/token_utils.h"

void	test_lex(t_token *head)
{
	t_token		*itter;
	size_t		len;

	printf("\ttest_lext\n");
	if (!head)
	{
		printf("(null)\n");
		return ;
	}
	itter = head;
	len = 0;
	while (itter != NULL)
	{
		if (itter->token_value)
			len = ft_strlen(itter->token_value);
		printf("token = %s\t| token_label = %d\t| token_index = %d\t| token_start = %d\t| token_end = %d\t| token_len = %zu\n", itter->token_value, itter->token_label, itter->i, itter->start_pos, itter->end_pos, len);
		itter = itter->next;
	}
	printf("\ttest_lex completed\n");
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
		printf("SECTION: %d\n", i);
		test_lex(itter->head);
		printf("\n");
		i++;
		itter = itter->next;
	}
	printf("\ttest_split completed\n\n");
}

void	test_split_cmd_rdir(t_split_cmd_rdir *split)
{
	printf("\tCOMMAND LIST:\n");
	test_lex(split->cmd_head);
	printf("\n\n\tREDIRECT IN LIST:\n");
	test_split(split->in_head);
	printf("\n\n\tREDIRECT OUT LIST:\n");
	test_split(split->out_head);
	printf("\ttest_split_cmd_rdir completed\n");
	printf("--------------------------------------\n\n");
}

void	test_filelst(t_file *head, bool is_infile)
{
	t_file	*temp;

	if (head == NULL)
		return ;
	if (is_infile == true)
		printf("\tinfiles:\n");
	else
		printf("\toutfiles:\n");
	temp = head;
	while (temp)
	{
		printf("filename: [%s]\t| filemode: [%d]\n", temp->filename, temp->mode);
		temp = temp->next;
	}	
}

void	test_simple_command(t_simple_cmd	*current)
{
	t_simple_cmd	*temp;
	int				cnt;

	temp = current;
	while (temp)
	{
		cnt = 0;
		printf("\tSIMPLE COMMAND %d:\n", current->index);
		printf("\tcommands:\n");
		if (temp->cmd != NULL)
		{
			while (temp->cmd[cnt])
			{
				printf("[%s]\n", temp->cmd[cnt]);
				cnt++;
			}
		}
		printf("\n");
		test_filelst(temp->infile_list, true);
		printf("\n");
		test_filelst(temp->outfile_list, false);
		printf("\n");
		temp = temp->next;
	}
}
