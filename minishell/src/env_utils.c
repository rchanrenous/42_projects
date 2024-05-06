/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:19:39 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/09 00:06:47 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_init(t_list **lst, char **envp)
{
	char	*content;
	t_list	*node;
	t_list	*tail;

	if (lst == NULL)
		return (0);
	*lst = NULL;
	tail = NULL;
	if (envp == NULL)
		return (1);
	while (*envp != NULL)
	{
		content = ft_strdup(*envp);
		if (content == NULL)
			return (ft_lstclear(lst, &free), 0);
		node = ft_lstnew(content);
		if (node == NULL)
			return (ft_lstclear(lst, &free), free(content), 0);
		ft_lstadd_back(&tail, node);
		if (*lst == NULL)
			*lst = node;
		tail = node;
		envp++;
	}
	return (1);
}

void	env_print(t_list *env)
{
	ft_lstiter(env, &lst_print_str);
}

int	is_var(void *content, void *var)
{
	if (valid_var_name(var))
		return (!var_in_env(var, content));
	return (1);
}

int	valid_var_name(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[i]))
		return (0);
	while (ft_isalnum(name[i]) || name[i] == '_')
		i++;
	return (name[i] == '\0' && i > 0);
}

int	var_in_env(char *var, char *env_var)
{
	int	len_var;

	if (var == NULL || env_var == NULL)
		return (0);
	len_var = ft_strlen(var);
	if (ft_strnstr(env_var, var, ft_strlen(env_var)) == env_var)
		if (env_var[len_var] == '=')
			return (len_var);
	return (0);
}
