/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:10:44 by rchan--r          #+#    #+#             */
/*   Updated: 2023/03/27 11:15:19 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_single_quote(char *str, t_list *env)
{
	int		i;
	char	*res;
	char	*rest;
	char	*join;

	if (str == NULL || *str != '\'')
		return (NULL);
	if (ft_strchr(str + 1, '\'') == NULL)
		return (NULL);
	i = 0;
	str++;
	while (str[i] != '\'')
		i++;
	res = ft_strldup(str, i + 1);
	if (res == NULL)
		return (NULL);
	str += i + 1;
	if (*str == '\0' || is_arg_delim(*str))
		return (res);
	rest = str_get_token(str, env);
	if (rest == NULL)
		return (free(res), NULL);
	join = ft_strjoin(res, rest);
	return (free(res), free(rest), join);
}
