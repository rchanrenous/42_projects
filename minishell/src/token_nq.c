/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_nq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:39:45 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/04 14:26:26 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}*/

static char	*token_nq_res(char *str, char *start, t_list *env)
{
	char	*res;
	char	*tmp;
	char	*end;

	tmp = NULL;
	if (is_expandable(str, NQ))
	{
		str += 1;
		tmp = token_expand(&str, env);
		if (tmp == NULL)
			return (free(start), NULL);
	}
	end = str_get_token(str, env);
	if (end == NULL)
		return (free(start), free(tmp), NULL);
	if (tmp == NULL)
		res = ft_strjoin(start, end);
	else
		res = ft_strjoin_sep(start, tmp, end);
	return (free(start), free(tmp), free(end), res);
}

static int	token_nq_cond(char *c)
{
	return (is_arg_delim(*c) || is_quote(*c) || is_expandable(c, NQ));
}

char	*token_no_quote(char *str, t_list *env)
{
	int		i;
	char	*start;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (!token_nq_cond(str + i))
		i++;
	start = ft_strldup(str, i + 1);
	str += i;
	if (start == NULL)
		return (NULL);
	if (is_arg_delim(*str))
		return (start);
	return (token_nq_res(str, start, env));
}
