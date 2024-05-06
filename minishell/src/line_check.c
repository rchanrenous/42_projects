/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:56:45 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/09 00:14:14 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_check_empty_cmd(t_list *list_cmd)
{
	t_cmd	*cmd;
	t_list	*node;

	node = list_cmd;
	while (node != NULL)
	{
		cmd = node->content;
		if (cmd->cmd[0] == NULL && cmd->list_redir == NULL)
		{
			if (list_cmd->next != NULL)
			{
				ft_printf_fd(2, "minishell: syntax error ");
				ft_printf_fd(2, "near unexpected token `|'\n");
				set_exit_status(2);
			}
			return (0);
		}
		node = node->next;
	}
	return (1);
}

int	redir_check(t_list *list_cmd)
{
	t_list	*list_redir;

	while (list_cmd != NULL)
	{
		list_redir = ((t_cmd *)list_cmd->content)->list_redir;
		while (list_redir != NULL)
		{
			if (((t_redir *)list_redir->content)->type == INVALID)
				return (0);
			if (((t_redir *)list_redir->content)->type == INVALID_PRINT)
				return (0);
			list_redir = list_redir->next;
		}
		list_cmd = list_cmd->next;
	}
	return (1);
}
