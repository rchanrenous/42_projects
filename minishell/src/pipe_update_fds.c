/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_update_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:22:29 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/07 20:22:46 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_close_old_fds(t_list *list_cmd)
{
	t_cmd	*cmd;
	t_cmd	*cmd_next;

	cmd = list_cmd->content;
	cmd_next = list_cmd->next->content;
	if (cmd->fds[WRITE] >= 3 && close(cmd->fds[WRITE]) < 0)
		return (0);
	if (cmd_next->fds[READ] >= 3 && close(cmd->fds[READ]) < 0)
		return (0);
	return (1);
}

int	pipe_update_fds(t_list *list_cmd)
{
	int	fds[2];

	if (list_cmd->next == NULL)
		return (1);
	if (pipe(fds) < 0)
	{
		if (list_cmd_close_fds(list_cmd, NR) == 0)
			return (0);
		return (0);
	}
	if (pipe_close_old_fds(list_cmd) == 0)
		return (0);
	((t_cmd *)list_cmd->content)->fds[WRITE] = fds[WRITE];
	((t_cmd *)list_cmd->next->content)->fds[READ] = fds[READ];
	return (1);
}
