/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:38:58 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/17 14:25:50 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_expand(char **str, t_list *env)
{
	int		i;
	char	*name;
	char	*res;

	if (str == NULL || *str == NULL)
		return (NULL);
	i = 0;
	if (**str == '?')
		return (*str += 1, ft_itoa(get_exit_status()));
	while ((*str)[i] != '\0' && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (name == NULL)
		return (NULL);
	ft_strlcpy(name, *str, i + 1);
	if (ft_getenv(name, env, &res) == 0)
		return (free(name), NULL);
	free(name);
	*str += i;
	if (res == NULL)
		return (ft_strdup(""));
	else
		return (res);
}

int	is_expandable(char *str, t_stype e)
{
	if (str == NULL || str[0] != '$')
		return (0);
	if (e == DQ)
		return (ft_isalnum(str[1]) || str[1] == '_' || str[1] == '?');
	else if (e == NQ)
		return (!is_arg_delim(str[1]));
	else if (e == NO)
		return (0);
	else
		return (1);
}
