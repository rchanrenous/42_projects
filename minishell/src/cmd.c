/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:46:50 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/09 01:28:08 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->cmd = NULL;
	new->list_redir = NULL;
	new->fds[WRITE] = 1;
	new->fds[READ] = 0;
	return (new);
}

void	cmd_free(t_cmd **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return ;
	tab_free(&((*cmd)->cmd));
	ft_lstclear(&((*cmd)->list_redir), &redir_free_void);
	free(*cmd);
	*cmd = NULL;
}

void	cmd_free_void(void *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	cmd_free(&tmp);
}

int	cmd_close_fds(t_cmd *cmd, t_close_fd close_fd)
{
	if (cmd == NULL || close_fd >= NR)
		return (0);
	if (cmd->fds[READ] >= 3 && close(cmd->fds[READ]) < 0)
		return (0);
	if (close_fd == CW && cmd->fds[WRITE] >= 3 && close(cmd->fds[WRITE]) < 0)
		return (0);
	return (1);
}

int	list_cmd_close_fds(t_list *list_cmd, t_close_fd close_fd)
{
	t_cmd	*cmd;

	if (list_cmd == NULL)
		return (0);
	cmd = list_cmd->content;
	if (cmd->fds[READ] >= 3 && close(cmd->fds[READ]) < 0)
		return (0);
	if (close_fd >= CW && cmd->fds[WRITE] >= 3 && close(cmd->fds[WRITE]) < 0)
		return (0);
	if (list_cmd->next != NULL && close_fd >= NR)
	{	
		cmd = list_cmd->next->content;
		if (close_fd >= NR && cmd->fds[READ] >= 3 && close(cmd->fds[READ]) < 0)
			return (0);
	}
	return (1);
}
