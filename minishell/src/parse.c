/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:00:46 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/09 04:38:25 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_print_invalid_token(t_list *list_redir, t_list *node_str)
{
	while (list_redir != NULL)
	{
		if (((t_redir *)list_redir->content)->type == INVALID_PRINT)
		{
			if (node_str->next == NULL)
				ft_printf_fd(2, "`newline'\n");
			else
				ft_printf_fd(2, "`|'\n");
		}
		list_redir = list_redir->next;
	}
}

static t_cmd	*cmd_from_str(t_list *node_str, t_list *env)
{
	t_cmd	*new;
	char	**tab;
	t_list	*lst;

	if (node_str->content == NULL)
		return (NULL);
	new = cmd_new();
	if (new == NULL)
		return (NULL);
	lst = parse_cmd(node_str->content, &(new->list_redir));
	if (lst == NULL)
		return (cmd_free(&new), NULL);
	redir_print_invalid_token(new->list_redir, node_str);
	tab = ft_lst_to_tab(lst);
	if (tab == NULL)
		return (cmd_free(&new), ft_lstclear(&lst, &free), NULL);
	ft_lstclear(&lst, &lst_no_free);
	new->cmd = tab;
	if (cmd_resolve_quotes(new, env) == 0)
		return (cmd_free(&new), NULL);
	return (new);
}

static int	lst_add_cmd(t_list **list_cmd, t_cmd *cmd)
{
	t_list	*node;

	node = ft_lstnew(cmd);
	if (node == NULL)
		return (ft_lstclear(list_cmd, &cmd_free_void), 0);
	ft_lstadd_back(list_cmd, node);
	return (1);
}

static int	line_check(char *line, t_list **list_cmd)
{
	*list_cmd = NULL;
	if (line == NULL)
		return (0);
	if (closed_quotes(line) == 0)
	{
		ft_printf_fd(2, "minishell: syntax error: unclosed quotes\n");
		*list_cmd = ft_lstnew(NULL);
		if (*list_cmd == NULL)
			return (0);
		return (-1);
	}
	return (1);
}

t_list	*parse(char *line, t_list *env)
{
	char	*exp;
	t_list	*list_str;
	t_list	*list_cmd;
	t_list	*tmp;
	t_cmd	*cmd;

	if (line_check(line, &list_cmd) != 1)
		return (list_cmd);
	exp = str_expand_nq(line, env);
	if (exp == NULL)
		return (NULL);
	list_str = line_to_cmds(exp);
	free(exp);
	if (list_str == NULL)
		return (NULL);
	list_cmd = NULL;
	tmp = list_str;
	while (tmp != NULL)
	{
		cmd = cmd_from_str(tmp, env);
		if (cmd == NULL || lst_add_cmd(&list_cmd, cmd) == 0)
			return (ft_lstclear(&list_str, &free), cmd_free(&cmd), NULL);
		tmp = tmp->next;
	}
	return (ft_lstclear(&list_str, &free), list_cmd);
}
