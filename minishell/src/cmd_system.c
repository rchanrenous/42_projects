/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_system.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:43:22 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 16:51:04 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path(char *cmd, char *dir, char **exec_path)
{
	int		len_dir;
	char	*dir_valid;
	char	*pathname;

	len_dir = ft_strlen(dir);
	if (len_dir == 0)
		return (0);
	if (dir[len_dir - 1] != '/')
		dir_valid = ft_strjoin(dir, "/");
	else
		dir_valid = ft_strdup(dir);
	if (dir_valid == NULL)
		return (0);
	pathname = ft_strjoin(dir_valid, cmd);
	free(dir_valid);
	if (pathname == NULL)
		return (0);
	if (access(pathname, F_OK) == 0)
	{
		free(*exec_path);
		*exec_path = pathname;
		return (1);
	}
	free(pathname);
	return (-1);
}

static int	get_path(char *cmd, char *var_path, char **exec_path)
{
	char	**dir;
	char	**tmp;
	int		res;

	if (exec_path == NULL)
		return (0);
	if (var_path[0] == ':' && access(*exec_path, F_OK) == 0)
		return (1);
	dir = ft_split(var_path, ':');
	if (dir == NULL)
		return (0);
	tmp = dir;
	while (*dir != NULL)
	{
		res = check_path(cmd, *dir, exec_path);
		if (res == 0 || res == 1)
			return (tab_free(&tmp), res);
		dir++;
	}
	tab_free(&tmp);
	if (var_path[ft_strlen(var_path) - 1] == ':' && !access(*exec_path, F_OK))
		return (1);
	return (-1);
}

static int	exec_path_error_message(char *e_p, int res, char *var_path)
{
	int	tmp;

	if (res == 1)
	{
		tmp = is_dir_message(e_p);
		if (tmp != -1)
			return (free(e_p), -tmp);
		if (access(e_p, X_OK) == -1)
		{
			ft_printf_fd(2, "minishell: %s: Permission denied\n", e_p);
			return (set_exit_status(126), free(e_p), -1);
		}
		return (1);
	}
	if (res == -1)
	{
		set_exit_status(127);
		if (var_path == NULL || ft_strchr(e_p, '/') != NULL)
			ft_printf_fd(2, "minishell: %s: No such file or directory\n", e_p);
		else
			ft_printf_fd(2, "%s: command not found\n", e_p);
	}
	free(e_p);
	return (res);
}

static int	call_system(char *exec_path, t_list *ls_cmd, t_list *env, int *n)
{
	char	**env_tab;
	int		pid;
	t_cmd	*cmd;

	cmd = ls_cmd->content;
	env_tab = NULL;
	if (env != NULL)
	{
		env_tab = ft_lst_to_tab(env);
		if (env_tab == NULL)
			return (free(exec_path), 0);
	}
	set_exit_status(0);
	pid = fork();
	if (pid == 0)
	{
		if (dup2(cmd->fds[READ], 0) == -1 || dup2(cmd->fds[WRITE], 1) == -1)
			return (set_exit_status(1), free(env_tab), free(exec_path), 0);
		if (ls_cmd->next && close(((t_cmd *)ls_cmd->next->content)->fds[READ]))
			return (set_exit_status(1), free(env_tab), free(exec_path), 0);
		if (execve(exec_path, cmd->cmd, env_tab) == -1)
			return (set_exit_status(1), free(env_tab), free(exec_path), 0);
	}
	return (free(exec_path), free(env_tab), *n += 1, 1);
}

int	cmd_system(t_list *list_cmd, t_list *env, int *nb_process)
{
	char	*var_path;
	char	*exec_path;
	int		res;
	t_cmd	*cmd;

	set_exit_status(1);
	cmd = list_cmd->content;
	exec_path = ft_strdup(cmd->cmd[0]);
	res = -1;
	if (exec_path == NULL || ft_getenv("PATH", env, &var_path) == 0)
		return (free(exec_path), 0);
	if (var_path != NULL)
	{
		if (ft_strchr(cmd->cmd[0], '/') == NULL)
			res = get_path(cmd->cmd[0], var_path, &exec_path);
		else if (access(exec_path, F_OK) == 0)
			res = 1;
		free(var_path);
	}
	else if (access(exec_path, F_OK) == 0)
		res = 1;
	res = exec_path_error_message(exec_path, res, var_path);
	if (res == 0 || res == -1)
		return (res);
	return (call_system(exec_path, list_cmd, env, nb_process));
}
