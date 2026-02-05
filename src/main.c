/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/05 01:20:04 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char		*line;
	t_cmdtab	cmdtab;

	(void)av;
	if (ac != 1)
		return (write(1, "\e[1;31mInvalid arguments\e[0m\n", 29));
	signal_manager();
	if (copy_env(&cmdtab, ev))
		return (1);
	line = (char *)1;
	while (line)
	{
		line = readline("Minishell> ");
		rl_on_new_line();
		if (all_whitespace(line))
			continue ;
		if (!0)
		{
			;
		}
		add_history(line);
		free(line);
	}
}
