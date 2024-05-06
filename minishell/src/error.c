/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:57:47 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/17 15:29:34 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir_message(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (dir != NULL)
	{
		if (closedir(dir) < 0)
			return (0);
		ft_printf_fd(2, "minishell: %s: Is a directory\n", str);
		set_exit_status(126);
		return (1);
	}
	else if (errno != ENOTDIR && errno != ENOENT)
		return (set_exit_status(1), 0);
	else
		return (-1);
}

int	check_dir_message(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (dir != NULL)
	{
		if (closedir(dir) < 0)
			return (0);
		return (1);
	}
	else if (errno == ENOTDIR)
	{
		ft_printf_fd(2, "minishell: cd: %s: Not a directory\n", str);
		return (set_exit_status(1), -1);
	}
	else if (errno == ENOENT)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", str);
		return (set_exit_status(1), -1);
	}
	return (set_exit_status(0), 0);
}

int	cd_no_arg(char **arg, t_list *env)
{
	if (ft_getenv("HOME", env, arg) == 0)
		return (set_exit_status(1), 0);
	if (*arg == NULL)
	{
		ft_printf_fd(2, "minishell: cd: HOME not set\n");
		set_exit_status(1);
		return (-1);
	}
	return (1);
}
