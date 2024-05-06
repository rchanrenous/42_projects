/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:22:25 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 16:36:23 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_option(char *str)
{
	int	i;

	if (ft_strncmp(str, "-n", 2) != 0)
		return (0);
	i = 2;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	nl;

	set_exit_status(1);
	if (cmd == NULL || cmd->cmd == NULL || cmd->cmd[0] == NULL)
		return (0);
	if (ft_strcmp(cmd->cmd[0], "echo") != 0)
		return (0);
	set_exit_status(0);
	if (cmd->cmd[1] == NULL)
		return (ft_printf_fd(cmd->fds[WRITE], "\n"), 1);
	i = 1;
	nl = 1;
	while (cmd->cmd[i] != NULL && is_n_option(cmd->cmd[i]) == 1 && i++)
		nl = 0;
	while (cmd->cmd[i] != NULL)
	{
		ft_printf_fd(cmd->fds[WRITE], "%s", cmd->cmd[i]);
		if (cmd->cmd[i + 1] != NULL)
			ft_printf_fd(cmd->fds[WRITE], " ");
		i++;
	}
	if (nl == 1)
		ft_printf_fd(cmd->fds[WRITE], "\n");
	return (1);
}
