/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 11:03:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/08/19 15:05:36 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h> //path max
#include <unistd.h> //getcwd 

#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <string.h>
#include <stdbool.h>
#include "libft.h"
#include "lexer.h"

t_token *new_node(int index, int label, char *value)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	new->i = index;
	new->token_label = label;
	new->token_value = value;
	new->next = NULL;
	return (new);
}

t_token	*tokenlst_last(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	add_token_to_list(t_token **head, char *token_value, int *token_label)
{
	static int count;
	t_token *node;

	if (!token_value || !head)
		return ;
	count = count + 1;
	node = new_node(count, *token_label, token_value);
	*token_label = NO_LABEL;
	if (!*head)
		*head = node;
	else
		tokenlst_last(*head)->next = node;
}

bool	is_special_char(char current)
{
	if (current == '<' || current == '>' || current == '|')
		return (true);
	return (false);
}

bool	is_end_of_input(char current_plus_one)
{
	if (current_plus_one == '\0')
		return (true);
	return (false);
}

bool	is_token_separator(char current)
{
	if (current == ' ' || current == '<' || current == '>' || current == '|')
		return (true);
	return (false);
}

bool	is_literal(char current)
{
	if (current == '"' || current == 39)// dit moet wel passen, dus niet als " en dan ' 
		return (true);
	return (false);
}





char	*allocate_token_value(char *ret, int count, int i)
{
	char *token;

	if (count == 0)
		return (NULL);
	token = malloc(sizeof(char) * count + 1);
	ft_strlcpy(token, &ret[i], count + 1);
	return (token);
}

char	*do_special_char(char *ret, int *i_ref)
{
	int i;
	char *token;
	int	count;

	i = *i_ref;
	count = 1;
	token = NULL;
	while (ret[i] == ' ' && ret[i + 1] == ' ')
	{
		i++;
		*i_ref = *i_ref + 1;
	}
	if (is_special_char(ret[i]))
	{
		if ((ret[i] == '>' && ret[i + 1] == '>')
		|| (ret[i] == '<' && ret[i + 1] == '<'))
		{
			count++;
			*i_ref = *i_ref + 1;
		}
		token = allocate_token_value(ret, count, i);
	}
	return (token);
}


void	do_quotes(char *ret, int *i_ref, int *count_ref, int *token_label)
{
	//parser gaat handelen, zorg voor label, behoud quotes
	if (ret[*i_ref] == '"')
		*token_label = DOUBLE_QUOTE;
	else
		*token_label = SINGLE_QUOTE;
 	*i_ref = *i_ref + 1; //duw voorbij signal single quote
	*count_ref = *count_ref + 1;
	while(!is_literal(ret[*i_ref]))
	{
		*i_ref = *i_ref + 1;
		*count_ref = *count_ref + 1;
	}
}


void lex(char *ret)
{
	t_token	*head;
	t_token *itter;
	t_label_flag	label_flag;
	int		i;
	int		count;
	int		token_label;
	char	*token_value;

	i = 0;
	head = NULL;
	token_label = NO_LABEL;
	count = 0;

	while (ret[i])
	{
		if (is_token_separator(ret[i]))
		{
			token_value = allocate_token_value(ret, count, (i - count));
			add_token_to_list(&head, token_value, &token_label);
			token_value = do_special_char(ret, &i);
			add_token_to_list(&head, token_value, &token_label);
			count = -1;
		}
		if (is_end_of_input(ret[i + 1]))
		{
			token_value = allocate_token_value(ret, (count + 1), (i - count));
			add_token_to_list(&head, token_value, &token_label);
		}
		if (is_literal(ret[i]))
			do_quotes(ret, &i, &count, &token_label);
		i++;
		count++;
	}
	itter = head;
	while (itter)
	{
		printf("token = %s | token_label = %d\n", itter->token_value, itter->token_label);
		itter = itter->next;
	} 
}

int main()
{
	char *ret;
	char path_buffer[PATH_MAX];

	getcwd(path_buffer, sizeof(path_buffer));
	printf("%s\n", path_buffer);
	//ret = readline("minishell> ");
	ret = "<<hier dit\"probeer\"ik  is >test";
	lex(ret);
	while (ret != NULL)
	{
		ret = readline("SpeckledPadloper> ");
		lex(ret);
		add_history(ret);
		free(ret);
	}
	free(ret);
	exit (0);
}
