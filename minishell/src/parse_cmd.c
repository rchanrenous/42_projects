/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:20:17 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/09 04:39:21 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	goto_file(char **str, t_redir_type *type)
{
	int			i;
	static int	print = 0;

	if (**str == *(*str + 1))
		(*str)++;
	(*str)++;
	i = 0;
	while (ft_isspace((*str)[i]))
		i++;
	if ((*str)[i] != '\0' && !is_redir((*str)[i]))
		return (*str += i, 1);
	set_exit_status(2);
	*type = INVALID;
	if (print == 0)
	{
		print++;
		ft_printf_fd(2, "minishell: syntax error near unexpected token ");
		if ((*str)[i] == '\0')
			*type = INVALID_PRINT;
		else if (is_redir((*str)[i + 1]) && (*str)[i + 1] == (*str)[i])
			ft_printf_fd(2, "`%c%c'\n", (*str)[i], (*str)[i + 1]);
		else
			ft_printf_fd(2, "`%c'\n", (*str)[i]);
	}
	return (*str += ft_strlen(*str), 1);
}

static int	str_redir_arg(char **str, t_redir *redir)
{
	int	i;
	int	end_quote;

	if (goto_file(str, &redir->type) == 0)
		return (1);
	i = 0;
	while ((*str)[i] != '\0' && !ft_isspace((*str)[i]) && !is_redir((*str)[i]))
	{
		if (is_quote((*str)[i]))
		{
			end_quote = index_end_token(*str + i);
			if (end_quote < 0)
				return (0);
			i += end_quote + 1;
		}
		else
			i++;
	}
	if (i > 0)
	{
		redir->arg = ft_strldup(*str, i + 1);
		if (redir->arg == NULL)
			return (0);
	}
	return (*str += i, 1);
}

static int	fill_redir(t_list **list_redir, char **str)
{
	t_redir_type	type;
	t_redir			*redir;
	t_list			*node;

	if (get_redir_type(*str, &type) == 0)
		return (0);
	redir = redir_new(type);
	if (redir == NULL)
		return (0);
	if (str_redir_arg(str, redir) == 0)
		return (redir_free(&redir), 0);
	node = ft_lstnew(redir);
	if (node == NULL)
		return (redir_free(&redir), 0);
	ft_lstadd_back(list_redir, node);
	return (1);
}

static int	parse_token(t_list **lst, char **str)
{
	int		i;

	if (**str != '\0')
	{
		i = index_end_token(*str);
		if (i < 0)
			return (2);
		else if (lst_add_strldup(lst, *str, i + 2) == 0)
		{
			ft_lstclear(lst, &free);
			return (0);
		}
		*str += i + 1;
		return (1);
	}
	return (1);
}

t_list	*parse_cmd(char *str, t_list **list_redir)
{
	t_list	*lst;
	char	c;

	if (str == NULL || list_redir == NULL)
		return (NULL);
	lst = NULL;
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		c = *str;
		if (is_redir(c) && fill_redir(list_redir, &str) == 0)
		{
			ft_lstclear(&lst, &free);
			return (ft_lstclear(list_redir, &redir_free_void), NULL);
		}
		if (!is_redir(c) && parse_token(&lst, &str) != 1)
			return (ft_lstclear(list_redir, &redir_free_void), NULL);
	}
	if (lst == NULL)
	{
		if (lst_add_strldup(&lst, NULL, 0) == 0)
			return (ft_lstclear(list_redir, &redir_free_void), NULL);
	}
	return (lst);
}
