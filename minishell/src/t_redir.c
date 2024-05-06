/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:07:29 by rchan--r          #+#    #+#             */
/*   Updated: 2023/03/31 15:47:59 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redir_new(t_redir_type type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->arg = NULL;
	redir->type = type;
	return (redir);
}

void	redir_free(t_redir **redir)
{
	if (redir == NULL || *redir == NULL)
		return ;
	if ((*redir)->arg != NULL)
		free((*redir)->arg);
	free(*redir);
	*redir = NULL;
}

void	redir_free_void(void *redir)
{
	t_redir	*tmp;

	tmp = redir;
	redir_free(&tmp);
}

int	get_redir_type(char *str, t_redir_type *type)
{
	int	test;

	if (str == NULL || type == NULL || is_redir(*str) == 0)
		return (*type = INVALID, 0);
	test = (str[1] == str[0]);
	if (str[0] == '<')
	{
		*type = IN1;
		if (test)
			*type = IN2;
	}
	else
	{
		*type = OUT1;
		if (test)
			*type = OUT2;
	}
	return (1);
}
