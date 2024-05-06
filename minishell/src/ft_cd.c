/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 10:55:23 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 16:33:28 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_oldpwd(char **str, char *cwd, t_list **env)
{
	char	*tab[2];

	if (cwd != NULL)
	{
		*str = ft_strjoin("OLDPWD=", cwd);
		if (*str == NULL)
			return (0);
	}
	tab[1] = NULL;
	tab[0] = "OLDPWD";
	if (env_unset(env, tab, NO_PIPE) == 0)
		return (free(*str), 0);
	return (1);
}

static int	set_path_vars(char *cwd, t_list **env)
{
	char	*pwd;
	char	*tab[3];

	if (get_cwd_val(&pwd, *env, NO_VAR) == 0)
		return (0);
	tab[2] = NULL;
	tab[0] = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (tab[0] == NULL)
		return (0);
	tab[1] = NULL;
	if (set_oldpwd(tab + 1, cwd, env) == 0)
		return (free(tab[0]), 0);
	if (env_export(env, tab, NO_PIPE) == 0)
		return (free(tab[0]), free(tab[1]), 0);
	free(tab[0]);
	free(tab[1]);
	return (1);
}

static int	cd_get_arg(char **cmd, char **arg, t_list *env)
{
	int	res;

	if (cmd[1] == NULL)
	{
		res = cd_no_arg(arg, env);
		if (res != 1)
			return (res);
	}
	else
	{
		*arg = ft_strdup(cmd[1]);
		if (*arg == NULL)
			return (0);
	}
	return (1);
}

static void	check_dir_access(char *arg)
{
	if (errno == EACCES)
	{
		set_exit_status(127);
		ft_printf_fd(2, "cd: permission denied: %s\n", arg);
	}
}

int	ft_cd(char **cmd, t_list **env, t_exec_type exec_type)
{
	int		res;
	char	*arg;
	char	*cwd;

	set_exit_status(1);
	if (cmd == NULL || *cmd == NULL)
		return (0);
	if (cmd[1] != NULL && cmd[2] != NULL)
		return (ft_printf_fd(2, "minishell: cd: too many arguments\n"), -1);
	res = cd_get_arg(cmd, &arg, *env);
	if (res != 1)
		return (res);
	res = check_dir_message(arg);
	if (res != 1)
		return (free(arg), res);
	if (ft_getenv("PWD", *env, &cwd) == 0)
		return (free(arg), 0);
	if (exec_type == NO_PIPE && chdir(arg) != 0 && errno != EACCES)
		return (free(arg), free(cwd), 0);
	if (exec_type == NO_PIPE && set_path_vars(cwd, env) == 0)
		return (free(arg), free(cwd), 0);
	set_exit_status(0);
	check_dir_access(arg);
	return (free(arg), free(cwd), 1);
}
