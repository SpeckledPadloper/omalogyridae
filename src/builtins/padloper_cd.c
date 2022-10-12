/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/12 16:46:11 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include "../../libft/libft.h"

void	padloper_cd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	if (!cmd_list->cmd[1] || cmd_list->cmd[2])
		printf("too many or to little args\n");
	else
		chdir(cmd_list->cmd[1]);
	fprintf(stderr, "check cd\n");
	write(STDOUT_FILENO, "cd go to pipe\n", 14);
	return ;
}
