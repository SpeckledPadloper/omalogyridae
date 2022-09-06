/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 11:03:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/06 19:54:03 by mteerlin      ########   odam.nl         */
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

#define KNRM  "\e[0m"
#define KRED  "\e[1;31m"

t_token	*new_node(int index, char *value, int end_pos, int len)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->i = index;
	new->token_label = add_token_label(value[0], value[1]);
	new->token_value = value;
	new->start_pos = end_pos - len;
	new->end_pos = end_pos;
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

char	*allocate_token_value(char *ret, int count, int i)
{
	char	*token;

	if (count == 0)
		return (NULL);
	token = malloc(sizeof(char) * count + 1);
	ft_strlcpy(token, &ret[i], count + 1);
	return (token);
}

void	add_token_to_list(t_token **head, char *token_value, int i, int count)
{
	static int	token_index = 0;
	t_token		*node;

	if (!token_value || !head)
		return ;
	token_index = token_index + 1;
	node = new_node(token_index, token_value, i, count);
	if (!*head)
		*head = node;
	else
		tokenlst_last(*head)->next = node;
}

// void	stitch_token(t_token **token, char *stitch_value, int *stitch_label)
// {
// 	t_token	*node;

// 	if (!stitch_value || !token)
// 		return ;
// 	node = new_node(0, stitch_value);
// 	*stitch_label = NO_LABEL;
// 	if (!*token)
// 		*token = node;
// 	else
// 		tokenlst_last(*token)->next = node;
// }

int	add_token_label(char current, char next_char)
{
	int	token_label;

	token_label = 0;
	if (current == '<' && next_char != '<')
		token_label = LESS;
	else if (current == '<' && next_char == '<')
		token_label = LESSLESS;
	else if (current == '>' && next_char != '>')
		token_label = GREAT;
	else if (current == '>' && next_char == '>')
		token_label = GREATGREAT;
	else if (current == '|')
		token_label = PIPE;
	else if (current == '\'')
		token_label = SINGLE_QUOTE;	
	else if (current == '"')
		token_label = DOUBLE_QUOTE;
	else if (current == '$')
		token_label = EXPAND;
	else
		token_label = NO_LABEL;
	return (token_label);
}

//________________________________________________________________________________

bool	is_special_char(char current)
{
	if (current == '<' || current == '>' || current == '|' \
		|| current == '"' || current == '\'')
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
	if (current == ' ' || current == '<' || current == '>' || \
		current == '|' || current == '"' || current == '\'' || current == '$')
		return (true);
	return (false);
}

bool	is_literal(char current)
{
	if (current == '"' || current == 39) 
		return (true);
	return (false);
}

bool	is_closing_char(char current, int token_label)
{
	if (token_label == DOUBLE_QUOTE && current == '"')
		return (true);
	if (token_label == SINGLE_QUOTE && current == 39)
		return (true);
	else
		return (false);
}

//__________________________________________________________________________________________

char	*do_special_char(char *ret, int *i_ref)
{
	int		i;
	char	*token;
	int		count;

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
	*token_label = SINGLE_QUOTE;
 	(*i_ref)++; //duw voorbij signal single quote
	(*count_ref)++;
	while(!(ret[*i_ref] == '\''))
	{
		if (ret[*i_ref] == '\0') // error of specialcase
		{
			printf("\e[1;31m%s\e[0m\n", "missing closing char, lets implemet error or special_case here");
			break;
		}		
		(*i_ref)++;
		(*count_ref)++;
	}
}

void	single_quotes(char *ret, int *i_ref, int *count_ref, int *token_label)
{
	*token_label = SINGLE_QUOTE;
 	(*i_ref)++;
	(*count_ref)++;
	while(!is_closing_char(ret[*i_ref], *token_label))
	{
		if (ret[*i_ref] == '\0') // error of specialcase
		{
			printf("\e[1;31m%s\e[0m\n", "missing closing char, lets implemet error or special_case here");
			break;
		}		
		(*i_ref)++;
		(*count_ref)++;
	}
}

void lex(char *ret)
{
	t_token	*head;
	t_token *itter;
	int		i;
	int		count;
	char	*token_value;

	i = 0;
	count = 0;
	head = NULL;
	while (ret[i])
	{
		if (is_token_separator(ret[i]))
		{
			token_value = allocate_token_value(ret, count, (i - count));
			add_token_to_list(&head, token_value, i, count);
			token_value = do_special_char(ret, &i);
			add_token_to_list(&head, token_value, i, count);
			if (ret[i] == '$')
				count = 0;
			else
				count = -1;
		}
		else if (is_end_of_input(ret[i + 1]))
		{
			token_value = allocate_token_value(ret, (count + 1), (i - count));
			add_token_to_list(&head, token_value, i, count);
		}
		i++;
		count++;
	}
	itter = head;
	while (itter)
	{
		printf("token = %s\t| token_label = %d\t| token_index = %d\t| spos = [%d]\t| epos = [%d]\n", itter->token_value, itter->token_label, itter->i, itter->start_pos, itter->end_pos);
		itter = itter->next;
	}
}

t_base_args	*set_base_args(int argc, char **argv, char **env)
{
	t_base_args	*b_args;

	b_args = malloc(sizeof(t_base_args));
	b_args->argc = argc;
	b_args->argv = argv;
	b_args->env = env;
	return (b_args);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_base_args	*b_args;
	char		ctrl_d;

	b_args = set_base_args(argc, argv, env);
	input = " ";
	ctrl_d = '\0';
	while (input != NULL)
	{
		input = readline("SpeckledPadloper> ");
		lex(input);
		add_history(input);
		free(input);
	}
}

// int main()
// {
// 	char *ret;
// 	char path_buffer[PATH_MAX];

// 	getcwd(path_buffer, sizeof(path_buffer));
// 	printf("%s\n", path_buffer);
// 	//ret = readline("minishell> ");
// 	ret = "<<hier dit'probeer'ik  is >test";
// 	lex(ret);
// 	while (ret != NULL)
// 	{
// 		ret = readline("SpeckledPadloper> ");
// 		lex(ret);
// 		add_history(ret);
// 		free(ret);
// 	}
// 	free(ret);
// 	exit (0);
// }
