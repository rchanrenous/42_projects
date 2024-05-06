/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_protect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:55:45 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 16:53:26 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*start_protect(char *exp, int i, char *c)
{
	char	*start;
	char	*tmp;
	char	*protect;
	char	*res;

	if (is_quote(*c) == 0)
		return (NULL);
	start = ft_strldup(exp, i + 1);
	if (start == NULL)
		return (NULL);
	tmp = ft_strldup(exp + i, 2);
	if (tmp == NULL)
		return (free(start), NULL);
	protect = ft_strjoin_sep(c, tmp, c);
	free(tmp);
	if (protect == NULL)
		return (free(start), NULL);
	res = ft_strjoin(start, protect);
	free(start);
	free(protect);
	return (res);
}

static int	is_protected_char(char *str, t_str_protect type)
{
	if (*str == '\0' || is_redir_pipe_exp(str, NO) || is_quote(*str))
		return (1);
	if (type == HEREDOC && (*str == ' ' || *str == '\n'))
		return (1);
	return (0);
}

char	*str_protect(char *exp, t_str_protect type)
{
	int		i;
	char	*protect;
	char	*rest;
	char	*res;

	i = 0;
	while (is_protected_char(exp + i, type) == 0)
		i++;
	if (exp[i] == '\0')
		return (ft_strldup(exp, i + 1));
	else if (exp[i] != '\'')
		protect = start_protect(exp, i, "'");
	else
		protect = start_protect(exp, i, "\"");
	if (protect == NULL)
		return (NULL);
	rest = str_protect(exp + i + 1, type);
	if (rest == NULL)
		return (free(protect), NULL);
	res = ft_strjoin(protect, rest);
	return (free(protect), free(rest), res);
}
