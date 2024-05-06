/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:14:57 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 13:56:59 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int fd)
{
	char	*cwd;

	set_exit_status(1);
	if (get_cwd_val(&cwd, NULL, NO_VAR) == 0)
		return (0);
	if (cwd == NULL)
		return (0);
	ft_printf_fd(fd, "%s\n", cwd);
	free(cwd);
	set_exit_status(0);
	return (1);
}
