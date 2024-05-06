/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 03:17:21 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/09 04:31:45 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_heredoc(int sig)
{
	(void)sig;
	ft_printf_fd(2, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handler_exec(int sig)
{
	if (sig == SIGQUIT)
	{
		set_exit_status(131);
		ft_printf_fd(2, "Quit (core dumped)\n");
	}
	else if (sig == SIGINT)
	{
		set_exit_status(130);
		ft_printf_fd(2, "\n");
	}
}

static void	handler_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf_fd(2, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		set_exit_status(130);
	}
}

void	sig_setup(t_exec_mode mode)
{
	if (mode == EXEC)
	{
		signal(SIGQUIT, &handler_exec);
		signal(SIGINT, &handler_exec);
	}
	else if (mode == PROMPT)
	{
		signal(SIGINT, &handler_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC_READ)
	{
		signal(SIGINT, &handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
