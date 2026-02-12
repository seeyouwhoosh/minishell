/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 01:26:00 by xwu               #+#    #+#             */
/*   Updated: 2026/02/13 00:30:56 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_signal(t_cmdtab *cmdtab)
{
	if (g_signal == SIGINT)
	{
		cmdtab->exit_code = 130;
		g_signal = 0;
	}
}

void	global_int_signal(int n)
{
	(void)n;
	signal(SIGINT, SIG_IGN);
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = SIGINT;
	signal(SIGINT, global_int_signal);
}

void	global_signal_manager(void)
{
	signal(SIGINT, global_int_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	parent_signal_manager(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signal_manager(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
