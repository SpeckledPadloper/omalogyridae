/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 14:05:26 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/10/26 18:28:53 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>

static void	interrupt_handler(int sig)
{
	int	status;
	status = 0;
	fprintf(stderr, "wp signal terminated?? [%d] with: [%d] exitstat [%d] \n", WIFSIGNALED(status), WTERMSIG(status), WEXITSTATUS(status));
}
