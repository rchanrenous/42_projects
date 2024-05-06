/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_end_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:39:45 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/04 14:24:59 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	index_end_token_quote(char *line)
{
	char	c;
	int		i;
	int		end_rest;

	c = line[0];
	i = 1;
	while (line[i] != '\0' && line[i] != c)
		i++;
	if (line[i] != c)
		return (-1);
	if (!is_arg_delim(line[i + 1]))
	{
		end_rest = index_end_token(line + i + 1);
		if (end_rest < 0)
			return (-1);
		return (i + 1 + end_rest);
	}
	else
		return (i);
}

static int	index_end_token_redir(char *line)
{
	if (line[1] == line[0])
		return (1);
	return (0);
}

static int	cond_end_token_no_quote(char *str)
{
	if (*str == '\0' || ft_isspace(*str) || is_quote(*str))
		return (1);
	if (is_redir_pipe_exp(str, NQ))
		return (1);
	return (0);
}

static int	index_end_token_no_quote(char *line)
{
	int	i;
	int	end_rest;

	i = 0;
	while (cond_end_token_no_quote(line + i) == 0)
		i++;
	if (!line[i] || ft_isspace(line[i]) || is_redir_pipe_exp(line + i, NQ))
		return (i - 1);
	else if (is_quote(line[i]))
	{
		end_rest = index_end_token(line + i);
		if (end_rest < 0)
			return (-1);
		return (i + end_rest);
	}
	return (-1);
}

int	index_end_token(char *line)
{
	if (line == NULL)
		return (-1);
	if (is_expandable(line, NQ))
		return (-1);
	if (line[0] == '\0' || ft_isspace(line[0]))
		return (0);
	if (is_quote(line[0]))
		return (index_end_token_quote(line));
	if (is_redir(line[0]))
		return (index_end_token_redir(line));
	if (line[0] == '|')
		return (0);
	else
		return (index_end_token_no_quote(line));
}
