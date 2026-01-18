/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 01:26:00 by xwu               #+#    #+#             */
/*   Updated: 2026/01/18 13:18:24 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	int_signal(int n)
{
	(void)n;
	signal(SIGINT, SIG_IGN);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGINT, int_signal);
}

void	signal_manager()
{
	signal(SIGINT, int_signal);
	signal(SIGQUIT, SIG_IGN);
}
