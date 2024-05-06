/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:36:45 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/08 22:59:51 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env, int fd)
{
	while (env != NULL)
	{
		ft_printf_fd(fd, "%s\n", env->content);
		env = env->next;
	}
	set_exit_status(0);
	return (1);
}
