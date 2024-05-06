/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:16:56 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 16:41:42 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_unset(t_list **env, char **cmd, t_exec_type exec_type)
{
	set_exit_status(1);
	if (env == NULL || cmd == NULL)
		return (0);
	set_exit_status(0);
	if (exec_type == PIPE)
		return (1);
	while (*cmd != NULL)
	{
		ft_lstfree_cmp(env, *cmd, &is_var);
		cmd++;
	}
	return (1);
}
