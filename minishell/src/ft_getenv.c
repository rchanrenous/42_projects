/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:19:39 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 16:37:24 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getenv(char *var, t_list *env, char **res)
{
	int		len_var;

	if (var == NULL || res == NULL)
		return (0);
	while (env != NULL)
	{
		len_var = var_in_env(var, env->content);
		if (len_var > 0)
		{
			*res = ft_strdup(env->content + len_var + 1);
			if (*res == NULL)
				return (set_exit_status(1), 0);
			return (1);
		}
		env = env->next;
	}
	*res = NULL;
	return (1);
}
