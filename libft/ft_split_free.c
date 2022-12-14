/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_free.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 17:12:42 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/06 15:46:58 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_split(char	**split)
{
	char	*itter;
	int		cnt;

	if (!split)
		return ;
	cnt = 0;
	itter = split[cnt];
	while (itter)
	{
		free(itter);
		cnt++;
		itter = split[cnt];
	}
	free(split);
}
