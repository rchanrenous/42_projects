/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:20:01 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 17:25:54 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_exit_status = 0;

void	set_exit_status(int val)
{
	g_exit_status = val;
}

int	get_exit_status(void)
{
	return (g_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;

	(void) argv;
	if (argc != 1 || env_init(&env, envp) == 0)
		return (0);
	while (line_exec(&env) != 0)
		;
	ft_lstclear(&env, &free);
	return (g_exit_status);
}
