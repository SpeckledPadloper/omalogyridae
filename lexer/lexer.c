/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 11:03:49 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/09/13 19:57:52 by mteerlin      ########   odam.nl         */
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
#include "../libft/libft.h"
#include "lexer.h"

#define KNRM  "\e[0m"
#define KRED  "\e[1;31m"

t_token	*new_node(int index, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->i = index;
	new->token_label = add_token_label(value[0], value[1]);
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

char	*allocate_token_value(char *ret, int count, int i)
{
	char	*token;

	if (i < 0)
		return (NULL);
	token = malloc(sizeof(char) * (count + 1));
	ft_strlcpy(token, &ret[i], count + 1);
	return (token);
}

void	add_token_to_list(t_token **head, char *token_value)
{
	static int	token_index = 0;
	t_token		*node;

	if (!token_value || !head)
		return ;
	token_index = token_index + 1;
	node = new_node(token_index, token_value);
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

bool	is_whitespace(char current)
{
	if (current == ' ' || (current > 8 && current < 14))
		return (true);
	return (false);
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
	if (is_whitespace(current) || current == '<' || current == '>' || \
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

// void	do_quotes(char *ret, int *i_ref, int *count_ref, int *token_label)
// {
// 	//parser gaat handelen, zorg voor label, behoud quotes
// 	*token_label = SINGLE_QUOTE;
//  	(*i_ref)++; //duw voorbij signal single quote
// 	(*count_ref)++;
// 	while(!(ret[*i_ref] == '\''))
// 	{
// 		if (ret[*i_ref] == '\0') // error of specialcase
// 		{
// 			printf("\e[1;31m%s\e[0m\n", "missing closing char, lets implemet error or special_case here");
// 			break;
// 		}		
// 		(*i_ref)++;
// 		(*count_ref)++;
// 	}
// }

// void	single_quotes(char *ret, int *i_ref, int *count_ref, int *token_label)
// {
// 	*token_label = SINGLE_QUOTE;
//  	(*i_ref)++;
// 	(*count_ref)++;
// 	while(!is_closing_char(ret[*i_ref], *token_label))
// 	{
// 		if (ret[*i_ref] == '\0') // error of specialcase
// 		{
// 			printf("\e[1;31m%s\e[0m\n", "missing closing char, lets implemet error or special_case here");
// 			break;
// 		}		
// 		(*i_ref)++;
// 		(*count_ref)++;
// 	}
// }

char	*do_special_char(char *ret, int *i_ref)
{
	char	*token;
	int		i;
	int		count;

	i = *i_ref;
	count = 1;
	token = NULL;
	if ((ret[*i_ref] == '>' && ret[*i_ref + 1] == '>')
		|| (ret[*i_ref] == '<' && ret[*i_ref + 1] == '<'))
	{
		count++;
		(*i_ref)++;
	}
	token = allocate_token_value(ret, count, i);
	return (token);
}

void	lex(char *ret)
{
	t_token	*head;
	t_token	*itter;
	int		i;
	int		count;
	int		state;
	int		prev_state;

	i = 0;
	count = 0;
	head = NULL;
	state = STATE_START;
	while (ret[i])
	{
		printf("current character: %c\nstring pos: %d\n", ret[i], i);
		printf("token_len: %d\n", count);
		printf("state = %d\n", state);
		if (is_token_separator(ret[i]))
		{
			if (state == STATE_START)
			{
				if (is_whitespace(ret[i]))
					state = STATE_WS;
				else if (is_special_char(ret[i]))
				{
					add_token_to_list(&head, do_special_char(ret, &i));
					state = STATE_WS;
					count = -1;
				}
				else if (ret[i] == '\'')
					state = STATE_SQUOTE;
				else if (ret[i] == '"')
					state = STATE_DQUOTE;
				else if (ret[i] == '$')
					state = STATE_EXPAND;
				else
					state = STATE_COMMON;
			}
			else if (state == STATE_COMMON)
			{
				add_token_to_list(&head, allocate_token_value(ret, count, (i - count)));
				count = -1;
				if (is_whitespace(ret[i]))
					state = STATE_WS;
				else if (is_special_char(ret[i]))
				{
					add_token_to_list(&head, do_special_char(ret, &i));
					state = STATE_WS;
				}
				else if (ret[i] == '\'')
					state = STATE_SQUOTE;
				else if (ret[i] == '"')
					state = STATE_DQUOTE;
				if (ret[i] == '$')
					state = STATE_EXPAND;
			}
			else if (state == STATE_WS)
			{
				while (is_whitespace(ret[i]))
					i++;
				if (is_special_char(ret[i]))
				{
					add_token_to_list(&head, do_special_char(ret, &i));
					state = STATE_WS;
					count = -1;
				}
				else if (ret[i] == '\'')
					state = STATE_SQUOTE;
				else if (ret[i] == '"')
					state = STATE_DQUOTE;
				else if (ret[i] == '$')
					state = STATE_EXPAND;
				if (!is_special_char(ret[i]))
					count = 0;
			}
			else if (state == STATE_SQUOTE)
			{
				if (ret[i] == '\'')
				{
					add_token_to_list(&head, allocate_token_value(ret, count, (i - count)));
					state = STATE_WS;
					count = -1;
				}
			}
			else if (state == STATE_DQUOTE)
			{
				if (ret[i] == '"')
				{
					add_token_to_list(&head, allocate_token_value(ret, count, (i - count)));
					state = STATE_WS;
					count = -1;
				}
				else if (ret[i] == '$')
				{
					count--;
					add_token_to_list(&head, allocate_token_value(ret, count, (i - count)));
					state = STATE_EXPAND;
					prev_state = STATE_DQUOTE;
					count = 0;
				}
			}
			else if (state == STATE_EXPAND)
			{
				add_token_to_list(&head, allocate_token_value(ret, count, (i - count)));
				if (prev_state == STATE_DQUOTE)
				{
					if (ret[i] == '"')
					{
						state = STATE_WS;
						count = -1;
					}
					else
					{
						state = STATE_DQUOTE;
						count = 0;
					}
				}
				else if (is_special_char(ret[i]))
				{
					add_token_to_list(&head, do_special_char(ret, &i));
					state = STATE_WS;
					count = -1;
				}
				else
				{
					state = STATE_WS;
					count = 0;
				}
			}
		}
		else if (!(state == STATE_SQUOTE || state == STATE_DQUOTE || state == STATE_EXPAND))
			state = STATE_COMMON;
		if (is_end_of_input(ret[i + 1]) && state == STATE_COMMON)
			add_token_to_list(&head, allocate_token_value(ret, (count + 1), (i - count)));
		i++;
		count++;
	}
	itter = head;
	while (itter)
	{
		printf("token = %s\t| token_label = %d\t| token_index = %d\t| token_len = %zu\n", itter->token_value, itter->token_label, itter->i, ft_strlen(itter->token_value));
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
	printf("states: %d, %d, %d, %d, %d, %d, %d\n", STATE_START, STATE_WS, STATE_SPECIAL, STATE_SQUOTE, STATE_DQUOTE, STATE_EXPAND, STATE_COMMON);
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
