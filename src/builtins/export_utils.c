/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/13 16:57:52 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

char	*export_strcpy(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] == '=')
		{
			dest[j] = src[i];
			dest[j + 1] = '"';
			i++;
			j += 2;
		}
		if (src[i] == '\0')
			break ;
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '"';
	dest[j + 1] = '\0';
	if (i == j)
		dest[j] = '\0';
	return (dest);
}

void	populate_export(int size, char **src, char **dst)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (src[i][j])
			j++;
		dst[i] = (char *)malloc(sizeof(char) * j + 3);
		if (!dst)
			print_error_exit("malloc", errno, EXIT_FAILURE);
		export_strcpy(dst[i], src[i]);
		i++;
	}
	dst[i] = NULL;
}

bool	export_var_not_valid(char *var)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(var[0]) || var[0] == '_'))
		return (true);
	while (var[i] && var[i] != '=')
	{
		if (!(ft_isalnum(var[i]) || var[i] == '='))
			return (true);
		i++;
	}
	return (false);
}

void	sort_env(t_metadata *data)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < data->envp_size)
	{
		j = 1 + i;
		while (j < data->envp_size)
		{
			if (envcmp(data->sorted_print_export[i],
					data->sorted_print_export[j]) > 0)
			{
				temp = data->sorted_print_export[j];
				data->sorted_print_export[j] = data->sorted_print_export[i];
				data->sorted_print_export[i] = temp;
			}
			j++;
		}
		i++;
	}
}
