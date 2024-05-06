/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:19:39 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/17 14:42:50 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_assignment(char **name, char *str)
{
	char	*equal;

	*name = NULL;
	if (ft_strcmp(str, "") == 0)
	{
		ft_printf_fd(2, "minishell: export: `%s': ", str);
		ft_printf_fd(2, "not a valid identifier\n");
		return (set_exit_status(1), -1);
	}
	equal = ft_strchr(str, '=');
	if (equal == NULL)
		*name = ft_strdup(str);
	else
		*name = ft_strldup(str, equal - str + 1);
	if (*name == NULL)
		return (set_exit_status(1), 0);
	if (valid_var_name(*name) == 0)
	{
		ft_printf_fd(2, "minishell: export: `%s': ", str);
		ft_printf_fd(2, "not a valid identifier\n");
		return (set_exit_status(1), free(*name), *name = NULL, -1);
	}
	if (equal == NULL)
		return (-1);
	return (1);
}

static int	env_export_routine(t_list **env, char *cmd, t_exec_type exec_type)
{
	char	*var;
	t_list	*node;
	int		res;

	res = var_assignment(&var, cmd);
	if (res != 1)
		return (res);
	if (var != NULL && exec_type == NO_PIPE)
	{
		ft_lstfree_cmp(env, var, &is_var);
		free(var);
		var = ft_strdup(cmd);
		if (var == NULL)
			return (set_exit_status(1), 0);
		node = ft_lstnew(var);
		if (node == NULL)
			return (set_exit_status(1), free(var), 0);
		ft_lstadd_back(env, node);
	}
	return (1);
}

static void	lst_export_print(void *content)
{
	ft_printf("declare -x %s\n", content);
}

int	env_export(t_list **env, char **cmd, t_exec_type exec_type)
{
	int	res;
	int	count;
	int	i;

	if (env == NULL || cmd == NULL)
		return (0);
	if (*cmd == NULL)
		return (set_exit_status(0), ft_lstiter(*env, &lst_export_print), 1);
	i = 0;
	count = 0;
	while (cmd[i] != NULL)
	{
		res = env_export_routine(env, cmd[i], exec_type);
		if (res == 0)
			return (0);
		if (res == 1)
			count++;
		i++;
	}
	if (count > 0)
		set_exit_status(0);
	return (1);
}
