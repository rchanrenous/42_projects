/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_update_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:35:53 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/17 15:25:54 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_in1_update_fds(t_cmd *cmd, t_redir *redir)
{
	if (access(redir->arg, F_OK) == -1)
	{
		ft_printf_fd(2, "minishell: %s: ", redir->arg);
		ft_printf_fd(2, "No such file or directory\n");
		return (set_exit_status(1), -1);
	}
	else if (access(redir->arg, R_OK) == -1)
	{
		ft_printf_fd(2, "minishell: %s: ", redir->arg);
		ft_printf_fd(2, "Permission denied\n");
		return (set_exit_status(1), -1);
	}
	if (cmd_close_fds(cmd, CR) == 0)
		return (set_exit_status(1), 0);
	cmd->fds[READ] = open(redir->arg, O_RDONLY);
	if (cmd->fds[READ] < 0)
		return (set_exit_status(1), 0);
	return (1);
}

static int	arg_contains_dir(char *arg)
{
	char	*dir_name;
	char	*end_dir;
	DIR		*dir;

	end_dir = ft_strrchr(arg, '/');
	if (end_dir == NULL)
		return (1);
	if (end_dir[1] == '\0' && ft_printf_fd(2, "minishell: %s: ", arg))
		return (ft_printf_fd(2, "Is a directory\n"), set_exit_status(1), -1);
	dir_name = ft_strldup(arg, end_dir - arg + 2);
	if (dir_name == NULL)
		return (set_exit_status(1), 0);
	dir = opendir(dir_name);
	free(dir_name);
	if (dir != NULL)
	{
		if (closedir(dir) < 0)
			return (set_exit_status(1), 0);
		return (1);
	}
	else if (errno != ENOTDIR && errno != ENOENT)
		return (set_exit_status(1), 0);
	ft_printf_fd(2, "minishell: %s: No such file or directory\n", arg);
	return (set_exit_status(1), -1);
}

static int	redir_out_update_fds(t_cmd *cmd, t_redir *redir, int oflag)
{
	int	res;

	if (access(redir->arg, F_OK) == 0 && access(redir->arg, W_OK) == -1)
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", redir->arg);
		return (set_exit_status(1), -1);
	}
	res = is_dir_message(redir->arg);
	if (res == 1)
		return (-1);
	if (res == 0)
		return (0);
	res = arg_contains_dir(redir->arg);
	if (res != 1)
		return (res);
	if (cmd->fds[WRITE] >= 3 && close(cmd->fds[WRITE]) < 0)
		return (0);
	cmd->fds[WRITE] = open(redir->arg, O_WRONLY | O_CREAT | oflag, 0644);
	if (cmd->fds[WRITE] < 0)
		return (0);
	return (1);
}

int	redir_update_fds(t_cmd *cmd, t_list *env)
{
	t_list	*list_redir;
	t_redir	*redir;
	int		res;

	list_redir = cmd->list_redir;
	while (list_redir != NULL)
	{
		redir = list_redir->content;
		if (redir->type == IN1)
			res = redir_in1_update_fds(cmd, redir);
		else if (redir->type == IN2)
			res = redir_in2_update_fds(cmd, redir, env);
		else if (redir->type == OUT1)
			res = redir_out_update_fds(cmd, redir, O_TRUNC);
		else if (redir->type == OUT2)
			res = redir_out_update_fds(cmd, redir, O_APPEND);
		if (res == 0 || res == -1)
			return (res);
		list_redir = list_redir->next;
	}
	return (1);
}
