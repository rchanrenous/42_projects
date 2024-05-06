/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:54:04 by rchan--r          #+#    #+#             */
/*   Updated: 2023/03/23 16:32:58 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	index_end_quote(char *str)
{
	char	*end;

	if (str == NULL || !is_quote(*str))
		return (-1);
	end = ft_strchr(str + 1, *str);
	if (end == NULL)
		return (-1);
	return (end - str);
}

int	closed_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_quote(str[i]) == 0)
			i++;
		if (is_quote(str[i]))
		{
			c = str[i];
			i++;
			while (str[i] != '\0' && str[i] != c)
				i++;
			if (str[i] == '\0')
				return (0);
			i++;
		}
	}
	return (1);
}
