/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/12 21:47:33 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal = 0;

int	main(int ac, char **av, char **ev)
{
	char		*line;
	t_cmdtab	*cmdtab;
	int			flag;

	(void)av;
	global_signal_manager();
	if (ac != 1)
		return (ft_putendl_fd("\e[1;31mToo many arguments\e[0m\n", 2), 1);
	cmdtab = ft_calloc(1, sizeof(t_cmdtab));
	if (!cmdtab)
		return (1);
	if (init_cmdtab(cmdtab, ev))
		return (free(cmdtab), 1);
	line = (char *)1;
	while (line)
	{
		if (g_signal == SIGINT)
		{
			cmdtab->exit_code = 1;
			g_signal = 0;
		}

		line = readline("Minishell> ");
		if (!line)
			break ;
		rl_on_new_line();
		if (all_whitespace(line))
		{
			free(line);
			continue ;
		}
		/* if (!parsing_main(line, cmdtab))
			execute_line(cmdtab); */

/* -------------------- TESTING AREA --------------------- */
		/* cmdtab->cmds = calloc(2, sizeof(t_cmd));
		cmdtab->n_cmds = 1;
		cmdtab->cmds[0].here_doc = NULL;
		cmdtab->cmds[0].infile = 0;
		cmdtab->cmds[0].outfile = 1;
		cmdtab->cmds[0].split_cmd = ft_split_charset(line, TOKEN_DELIMITER);
		execute_all(cmdtab); */

		flag = parse_main(cmdtab, line);
		if (!flag)
		{
			for (size_t i = 0; i < cmdtab->n_cmds; i++)
			{
				printf("Cmd number %lu:\n", i);
				printf("infile: %i, outfile: %i, heredoc: %s\n", cmdtab->cmds[i].infile, cmdtab->cmds[i].outfile, cmdtab->cmds[i].here_doc);
				printf("Command: ");
				if (!cmdtab->cmds[i].split_cmd)
					printf("none");
				else
				{
					for (size_t j = 0; cmdtab->cmds[i].split_cmd[j]; j++)
						printf("%s ", cmdtab->cmds[i].split_cmd[j]);
				}
				printf("\n\n");
			}

			execute_all(cmdtab);
		}
		else
			cmdtab->exit_code = flag;
/* ------------------------------------------------------- */

		add_history(line);
		free_cmds(cmdtab);
		free(line);
		flag = 0;
	}
	free_cmdtab(cmdtab);
}
