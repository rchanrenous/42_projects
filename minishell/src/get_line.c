/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:22:26 by thrio             #+#    #+#             */
/*   Updated: 2023/04/14 15:34:47 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_prompt(char **prompt, t_list *env)
{
	char	*dir;
	char	*tmp;
	char	*user;

	*prompt = NULL;
	if (ft_getenv("USER", env, &user) == 0)
		return (0);
	if (get_cwd_val(&dir, env, VAR) == 0)
		return (free(user), 0);
	if (user == NULL)
	{
		*prompt = ft_strdup("$>");
		if (*prompt == NULL)
			return (free(dir), 0);
		return (free(dir), 1);
	}
	tmp = ft_strjoin_sep(user, "@", dir);
	free(user);
	free(dir);
	if (tmp == NULL)
		return (0);
	*prompt = ft_strjoin(tmp, "$>");
	if (*prompt == NULL)
		return (free(tmp), 0);
	return (free(tmp), 1);
}

int	get_line(char **line, t_list *env)
{
	char	*prompt;

	sig_setup(PROMPT);
	if (get_prompt(&prompt, env) == 0)
		return (set_exit_status(1), 0);
	*line = readline(prompt);
	free(prompt);
	if (*line == NULL)
		return (set_exit_status(1), 0);
	return (1);
}
