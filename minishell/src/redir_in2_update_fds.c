/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in2_update_fds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:51:05 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/14 15:26:33 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_error_message(char *line, char *arg)
{
	if (line == NULL)
		ft_printf_fd(2, HEREDOC_EOF, arg);
	free(line);
}

static int	read_heredoc(char *arg, char **heredoc)
{
	char	*line;
	char	*tmp;

	line = readline(">");
	while (line != NULL && ft_strcmp(line, arg) != 0)
	{
		tmp = *heredoc;
		if (*heredoc == NULL)
			*heredoc = ft_strdup(line);
		else
			*heredoc = ft_strjoin_sep(*heredoc, "\n", line);
		free(tmp);
		free(line);
		if (*heredoc == NULL)
			return (0);
		line = readline(">");
	}
	heredoc_error_message(line, arg);
	if (*heredoc == NULL)
		return (1);
	tmp = *heredoc;
	*heredoc = ft_strjoin(*heredoc, "\n");
	if (*heredoc == NULL)
		return (free(tmp), 0);
	return (free(tmp), 1);
}

static int	parse_heredoc(char **heredoc, t_list *env)
{
	char	*tmp;

	if (*heredoc != NULL)
	{
		tmp = str_protect(*heredoc, HEREDOC);
		free(*heredoc);
		if (tmp == NULL)
			return (*heredoc = NULL, 0);
		*heredoc = tmp;
		if (str_resolve_quotes(heredoc, env) == 0)
			return (free(*heredoc), 0);
	}
	return (1);
}

int	redir_in2_update_fds(t_cmd *cmd, t_redir *redir, t_list *env)
{
	int		fds_hd[2];
	char	*heredoc;

	if (cmd_close_fds(cmd, CR) == 0 || pipe(fds_hd) < 0)
		return (set_exit_status(1), 0);
	sig_setup(HEREDOC_READ);
	cmd->fds[READ] = fds_hd[READ];
	heredoc = NULL;
	if (!read_heredoc(redir->arg, &heredoc) || !parse_heredoc(&heredoc, env))
	{
		set_exit_status(1);
		if (close(fds_hd[WRITE]) < 0)
			return (0);
		return (0);
	}
	if (heredoc != NULL)
	{
		write(fds_hd[WRITE], heredoc, ft_strlen(heredoc));
		free(heredoc);
	}
	if (close(fds_hd[WRITE]) < 0)
		return (set_exit_status(1), 0);
	return (1);
}
