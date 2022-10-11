/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_pwd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/11 17:10:53 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "../executer/hdr/executer.h"
#include "../hdr/structs.h"
#include <limits.h>

void	padloper_pwd(t_metadata *data, t_exec_list_sim *cmd_list)
{
	char buf[PATH_MAX];

	if (!data || !cmd_list)
	{
		fprintf(stderr, "Parameters are NULL");
		exit(1);
	}
	if (!getcwd(buf, sizeof(buf)))
		print_error_exit("getcwd", errno, EXIT_FAILURE);
	printf("%s\n", buf);
	return ;
}
