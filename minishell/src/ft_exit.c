/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:40:12 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/08 23:00:38 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	exit_arg(char **cmd, t_exec_type exec_type)
{
	if (arg_is_numeric(cmd[1]) == 0)
	{
		ft_printf_fd(2, "minishell: exit: %s: ", cmd[1]);
		ft_printf_fd(2, "numeric argument required\n");
		set_exit_status(2);
	}
	else if (cmd[2] != NULL)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		set_exit_status(1);
		return (1);
	}
	else
		set_exit_status(ft_atoi(cmd[1]));
	if (exec_type == PIPE)
		return (1);
	return (0);
}

int	ft_exit(char **cmd, t_exec_type exec_type)
{
	set_exit_status(1);
	if (cmd == NULL || *cmd == NULL)
		return (0);
	if (ft_strcmp(cmd[0], "exit") != 0)
		return (0);
	if (exec_type == NO_PIPE)
		ft_printf_fd(2, "exit\n");
	if (cmd[1] != NULL)
		return (exit_arg(cmd, exec_type));
	set_exit_status(0);
	if (exec_type == PIPE)
		return (1);
	return (0);
}
