/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/06 20:31:35 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char		*line;
	t_cmdtab	*cmdtab;

	(void)av;
	if (ac != 1)
		return (ft_putendl_fd("\e[1;31mToo many arguments\e[0m\n", 1), 1);
	signal_manager();
	cmdtab = ft_calloc(1, sizeof(cmdtab));
	if (!cmdtab)
		return (1);
	if (init_cmdtab(cmdtab, ev))
		return (free(cmdtab), 1);
	line = (char *)1;
	while (line)
	{
		line = readline("Minishell> ");
		rl_on_new_line();
		if (all_whitespace(line))
			continue ;
/* 		if (!process_line(line, cmdtab))
			execute_line(cmdtab); */

/* -------------------- TESTING AREA --------------------- */
	cmdtab->cmds = calloc(2, sizeof(t_cmd));



/* ------------------------------------------------------- */

		add_history(line);
		free(line);
	}
}
