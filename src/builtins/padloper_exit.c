/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/19 13:51:54 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

bool	check_overflow(int plu_min, long long int result,
			const char *str, int i)
{
	if (ft_strlen(str) > 19 + (plu_min == -1))
		return (true);
	if (plu_min == -1 && str[i] > '8')
		return (true);
	if (plu_min == 1 && str[i] > '7')
		return (true);
	else
		return (false);
}

int	exit_atoi(const char *str, bool *overflow)
{
	int					i;
	int					plu_min;
	long long int		result;

	i = 0;
	plu_min = 1;
	result = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			plu_min *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result >= 922337203685477580)
			*overflow = (check_overflow(plu_min, result, str, i));
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * plu_min);
}

bool	var_not_numeric(char *var)
{
	int		i;
	bool	overflow;

	i = 0;
	overflow = false;
	if (var[0] == '+' || var[0] == '-')
		i++;
	while (var[i])
	{
		if (!ft_isdigit(var[i]))
			return (true);
		i++;
	}
	exit_atoi(var, &overflow);
	if (overflow)
		return (true);
	return (false);
}

void	padloper_exit(t_metadata *data, t_exec_list_sim *cmd_list)
{
	int	exitcode;

	if (data->cmd_count == 1)
		write(2, "exit\n", 5);
	if (!cmd_list->cmd[1])
		exit(EXIT_SUCCESS);
	if (var_not_numeric(cmd_list->cmd[1]))
	{
		builtin_error("exit: ", cmd_list->cmd[1], NOT_NUMERIC, data);
		data->exitstatus = 255;
	}
	else if (cmd_list->cmd[2])
	{
		builtin_error("exit", NULL, TOO_MANY, data);
		return ;
	}
	else
	{
		exitcode = 0;
		exitcode = ft_atoi(cmd_list->cmd[1]);
		data->exitstatus = exitcode;
	}
	exit(data->exitstatus);
}
