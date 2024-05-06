/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expand_nq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:45:21 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/04 17:08:50 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	repl_exp(char **str, int *i, char **res_exp, t_list *env)
{
	char	*start;
	char	*exp;
	char	*tmp;

	start = ft_strldup(*str, *i + 1);
	if (start == NULL)
		return (free(*res_exp), *res_exp = NULL, 0);
	*str += *i + 1;
	tmp = token_expand(str, env);
	if (tmp == NULL)
		return (free(*res_exp), *res_exp = NULL, free(start), 0);
	exp = str_protect(tmp, PARSING);
	free(tmp);
	if (exp == NULL)
		return (free(*res_exp), *res_exp = NULL, free(start), 0);
	tmp = *res_exp;
	*res_exp = ft_strjoin_sep(*res_exp, start, exp);
	free(tmp);
	free(start);
	free(exp);
	if (*res_exp == NULL)
		return (0);
	*i = 0;
	return (1);
}

static int	while_expand_nq(char **str, char **res_exp, int *i, t_list *env)
{
	char	*tmp;
	int		index_end;

	tmp = *str + *i;
	if (is_expandable(tmp, NQ) && !repl_exp(str, i, res_exp, env))
		return (0);
	else if (is_quote(*tmp))
	{
		index_end = index_end_quote(tmp);
		if (index_end < 0)
			return (0);
		*i += index_end + 1;
	}
	else if (!is_expandable(tmp, NQ) && !is_quote(*tmp))
		(*i)++;
	return (1);
}

char	*str_expand_nq(char *str, t_list *env)
{
	int		i;
	char	*res_exp;
	char	*start;
	char	*tmp;

	i = 0;
	res_exp = ft_strdup("");
	if (res_exp == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (while_expand_nq(&str, &res_exp, &i, env) == 0)
			return (NULL);
	}
	start = ft_strldup(str, i + 1);
	if (start == NULL)
		return (free(res_exp), NULL);
	tmp = res_exp;
	res_exp = ft_strjoin(res_exp, start);
	return (free(tmp), free(start), res_exp);
}
