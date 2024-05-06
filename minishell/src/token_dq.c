/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:39:45 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/04 14:25:48 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*token_append_expandable(char *res, char **str, int *i, t_list *env)
{
	char	*tmp;
	char	*exp;
	char	*res_exp;

	tmp = ft_strldup(*str, *i + 1);
	if (tmp == NULL)
		return (NULL);
	(*str) += *i + 1;
	exp = token_expand(str, env);
	if (exp == NULL)
		return (free(tmp), NULL);
	if (res == NULL)
		res_exp = ft_strjoin(tmp, exp);
	else
	{
		res_exp = ft_strjoin_sep(res, tmp, exp);
		free(res);
	}
	free(tmp);
	free(exp);
	*i = -1;
	return (res_exp);
}

static char	*str_join_token(char *start, char *tmp, char *end)
{
	if (tmp == NULL || end == NULL)
		return (NULL);
	if (start == NULL)
		return (ft_strjoin(tmp, end));
	else
		return (ft_strjoin_sep(start, tmp, end));
}

char	*token_double_quote(char *str, t_list *env)
{
	int		i;
	char	*res;
	char	*start;
	char	*tmp;
	char	*end;

	if (str == NULL || *str != '\"' || ft_strchr((str++) + 1, '\"') == 0)
		return (NULL);
	start = NULL;
	i = 0;
	while (str[i] != '\"')
	{
		if (is_expandable(str + i, DQ))
		{
			start = token_append_expandable(start, &str, &i, env);
			if (start == NULL)
				return (NULL);
		}
		i++;
	}
	tmp = ft_strldup(str, i + 1);
	str += i + 1;
	end = str_get_token(str, env);
	res = str_join_token(start, tmp, end);
	return (free(start), free(tmp), free(end), res);
}
