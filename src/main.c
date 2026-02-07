/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/07 17:13:06 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char		*line;
	t_cmdtab	*cmdtab;

	(void)av;
	if (ac != 1)
		return (ft_putendl_fd("\e[1;31mToo many arguments\e[0m\n", 2), 1);
	signal_manager();
	cmdtab = ft_calloc(1, sizeof(t_cmdtab));
	if (!cmdtab)
		return (1);
	if (init_cmdtab(cmdtab, ev))
		return (free(cmdtab), 1);
	line = (char *)1;
	while (line)
	{
		line = readline("Minishell> ");
		if (!line)
			break ;
		rl_on_new_line();
		if (all_whitespace(line))
		{
			free(line);
			continue ;
		}
/* 		if (!process_line(line, cmdtab))
			execute_line(cmdtab); */

/* -------------------- TESTING AREA --------------------- */
	cmdtab->cmds = calloc(2, sizeof(t_cmd));
	cmdtab->n_cmds = 1;
	cmdtab->cmds[0].here_doc = NULL;
	cmdtab->cmds[0].infile = 0;
	cmdtab->cmds[0].outfile = 1;
	cmdtab->cmds[0].split_cmd = ft_split_charset(line, TOKEN_DELIMITER);
	execute_all(cmdtab);
/* ------------------------------------------------------- */

		add_history(line);
		free_cmds(cmdtab);
		free(line);
	}
	free_cmdtab(cmdtab);
}
