/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 17:44:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2022/09/22 17:54:05 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hdr/parcer.h"
#include "../utils/hdr/token_utils.h"

#include "../tests/tests.h" //for testing, remove before handin
#include <stdio.h>

void	parce(t_token *head)
{
	t_token_section	*first;

	first = tokenlst_split(head);
	test_split(first);
	split_cmd_rdir(first);
}
