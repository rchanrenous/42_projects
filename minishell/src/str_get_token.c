/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_get_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:39:45 by rchan--r          #+#    #+#             */
/*   Updated: 2023/03/27 11:14:37 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_get_token(char *str, t_list *env)
{
	if (str == NULL)
		return (NULL);
	if (is_arg_delim(*str))
		return (ft_strdup(""));
	if (*str == '\'')
		return (token_single_quote(str, env));
	else if (*str == '\"')
		return (token_double_quote(str, env));
	else
		return (token_no_quote(str, env));
}
