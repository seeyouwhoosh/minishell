/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 01:26:00 by xwu               #+#    #+#             */
/*   Updated: 2026/01/30 18:47:58 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	int_signal(int n)
{
	(void)n;
	signal(SIGINT, SIG_IGN);
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGINT, int_signal);
}

void	signal_manager(void)
{
	signal(SIGINT, int_signal);
	signal(SIGQUIT, SIG_IGN);
}
