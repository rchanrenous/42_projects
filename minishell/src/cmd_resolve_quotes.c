/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_resolve_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:54:40 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/04 10:26:34 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_resolve_quotes(char **str, t_list *env)
{
	char	*res;

	res = str_get_token(*str, env);
	if (res == NULL)
		return (0);
	free(*str);
	*str = res;
	return (1);
}

static int	tab_resolve_quotes(char **tab, t_list *env)
{
	while (*tab != NULL)
	{
		if (str_resolve_quotes(tab, env) == 0)
			return (0);
		tab++;
	}
	return (1);
}

int	cmd_resolve_quotes(t_cmd *cmd, t_list *env)
{
	t_list	*lst;
	t_redir	*redir;

	if (tab_resolve_quotes(cmd->cmd, env) == 0)
		return (0);
	lst = cmd->list_redir;
	while (lst != NULL)
	{
		redir = lst->content;
		if (redir == NULL)
			return (0);
		if (redir->arg != NULL)
		{
			if (str_resolve_quotes(&redir->arg, env) == 0)
				return (0);
		}
		lst = lst->next;
	}
	return (1);
}

/*	if (tab_resolve_quotes(cmd->redir_in, env) == 0)
		return (0);
	if (tab_resolve_quotes(cmd->redir_out, env) == 0)
		return (0);*/
/*
int	lst_resolve_quotes(t_list *lst, char **env)
{
	char	*str;

	while (lst != NULL)
	{
		str = lst->content;
		if (str_resolve_quotes(&str, env) == 0)
			return (0);
		lst->content = str;
		lst = lst->next;
	}
	return (1);
}*/
