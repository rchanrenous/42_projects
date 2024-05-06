/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:54:04 by rchan--r          #+#    #+#             */
/*   Updated: 2023/03/23 16:32:42 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_redir_pipe_exp(char *str, t_stype type)
{
	if (str == NULL)
		return (-1);
	if (*str == '|' || *str == '<' || *str == '>' || is_expandable(str, type))
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_arg_delim(char c)
{
	if (ft_isspace(c) || c == '\0')
		return (1);
	return (0);
}
