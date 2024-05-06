/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_strldup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:32:03 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/05 11:59:40 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lst_add_strldup(t_list **lst, char *line, int i)
{
	char	*content;
	t_list	*node;

	if (lst == NULL || (line == NULL && i != 0))
		return (0);
	if (i == 0)
		content = NULL;
	else
	{
		content = ft_strldup(line, i);
		if (content == NULL)
			return (0);
	}
	node = ft_lstnew(content);
	if (node == NULL)
		return (free(content), 0);
	ft_lstadd_back(lst, node);
	return (1);
}
