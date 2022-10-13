/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padloper_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/13 10:01:06 by lwiedijk      #+#    #+#                 */
/*   Updated: 2022/10/13 16:54:04 by lwiedijk      ########   odam.nl         */
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

/* 

	cd without arg, hoeven we niet, en wat als Home is unset en alles? gewoon not supported doen?

	let op: 
	bash-3.2$ cd lsfjl
	bash: cd: lsfjl: No such file or directory

	bash-3.2$ cd test
	bash: cd: test: Not a directory

	bash-3.2$ cd out_noright 
	bash: cd: out_noright: Not a directory

	
	bash-3.2$ mkdir dir_noright
	bash-3.2$ chmod 000 dir_noright/
	bash-3.2$ cd dir_noright/
	bash: cd: dir_noright/: Permission denied

	-bij teveel of foute args boeit het niks als de eerste arg goed is?
	bash-3.2$ cd .. lsjfls
	bash-3.2$ pwd
	bash-3.2$ cd src mteerlin
	bash-3.2$ pwd
	/Users/lwiedijk/SpeckledPadloper/omalogyridae/src
	bash-3.2$ cd .. test.txt
	bash-3.2$ pwd
	/Users/lwiedijk/SpeckledPadloper/omalogyridae
	/Users/lwiedijk/SpeckledPadloper

 */
