/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:23:44 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 16:37:46 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cwd_val(char **cwd, t_list *env, t_cwd_type type)
{
	char	buf[SIZE_BUF_GETCWD];

	if (type == VAR)
	{
		if (ft_getenv("PWD", env, cwd) == 0)
			return (0);
		if (*cwd != NULL)
			return (1);
	}
	*cwd = getcwd(buf, sizeof(buf));
	if (*cwd == NULL && type == VAR)
	{
		*cwd = ft_strdup(".");
		if (*cwd == NULL)
			return (0);
		return (1);
	}
	else if (*cwd == NULL)
		return (0);
	*cwd = ft_strdup(*cwd);
	if (*cwd == NULL)
		return (0);
	return (1);
}
