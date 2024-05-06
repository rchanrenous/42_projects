/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:42:15 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 17:21:35 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_list_cmd(t_list *env)
{
	char	*line;
	t_list	*list_cmd;

	if (get_line(&line, env) == 0)
		return (NULL);
	list_cmd = parse(line, env);
	if (line != NULL && ft_strcmp(line, "") != 0)
		add_history(line);
	free(line);
	return (list_cmd);
}

static int	cmd_exec(t_list *ls_cmd, t_list **env, t_exec_type exec_typ, int *n)
{
	t_cmd	*cmd;

	cmd = ls_cmd->content;
	if (cmd == NULL || cmd->cmd == NULL)
		return (0);
	else if (cmd->cmd[0] == NULL)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (ft_cd(cmd->cmd, env, exec_typ));
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (ft_pwd(cmd->fds[WRITE]));
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (ft_exit(cmd->cmd, exec_typ));
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (ft_env(*env, cmd->fds[WRITE]));
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (env_export(env, (cmd->cmd) + 1, exec_typ));
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (env_unset(env, (cmd->cmd) + 1, exec_typ));
	else
		return (cmd_system(ls_cmd, *env, n));
}

static int	exec_routine(t_list *list_cmd, t_list **env, int *nb_process)
{
	int			res;
	t_exec_type	exec_type;

	exec_type = NO_PIPE;
	if (list_cmd->next != NULL)
		exec_type = PIPE;
	res = 0;
	while (list_cmd != NULL)
	{
		if (pipe_update_fds(list_cmd) == 0)
			return (set_exit_status(1), 0);
		res = redir_update_fds(list_cmd->content, *env);
		if (res == 1)
			res = cmd_exec(list_cmd, env, exec_type, nb_process);
		if (res == 0)
			return (list_cmd_close_fds(list_cmd, NR), 0);
		if (cmd_close_fds(list_cmd->content, CW) == 0)
			return (0);
		list_cmd = list_cmd->next;
	}
	return (res);
}

static void	get_child_exit_status(int stat_val)
{
	if (WIFEXITED(stat_val) != 0)
		set_exit_status(WEXITSTATUS(stat_val));
}

int	line_exec(t_list **env)
{
	t_list		*list_cmd;
	t_list		*tmp;
	int			nb_process;
	int			stat_val;

	nb_process = 0;
	list_cmd = get_list_cmd(*env);
	if (list_cmd == NULL)
		return (set_exit_status(1), 0);
	sig_setup(EXEC);
	tmp = list_cmd;
	if (list_cmd->content == NULL)
		return (set_exit_status(1), ft_lstclear(&list_cmd, &free), 1);
	if (redir_check(list_cmd) == 0 || line_check_empty_cmd(list_cmd) == 0)
		return (ft_lstclear(&tmp, &cmd_free_void), 1);
	if (exec_routine(list_cmd, env, &nb_process) == 0)
		return (ft_lstclear(&tmp, &cmd_free_void), 0);
	while (nb_process > 0)
	{
		nb_process--;
		waitpid(-1, &stat_val, 0);
		get_child_exit_status(stat_val);
	}
	return (ft_lstclear(&tmp, &cmd_free_void), 1);
}
