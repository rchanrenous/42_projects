/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:17:59 by rchan--r          #+#    #+#             */
/*   Updated: 2023/03/23 16:35:29 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*line_to_cmds(char *line)
{
	t_list	*lst;
	int		i;

	if (line == NULL || closed_quotes(line) == 0)
		return (NULL);
	lst = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|')
		{
			if (lst_add_strldup(&lst, line, i + 1) == 0)
				return (ft_lstclear(&lst, &free), NULL);
			line += i + 1;
			i = 0;
		}
		else if (is_quote(line[i]))
			i += index_end_quote(line + i) + 1;
		else
			i++;
	}
	if (lst_add_strldup(&lst, line, i + 1) == 0)
		return (ft_lstclear(&lst, &free), NULL);
	return (lst);
}
