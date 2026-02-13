/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/13 18:38:09 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal = 0;

void	main_loop(t_cmdtab *cmdtab)
{
	char	*line;
	int		flag;

	line = (char *)1;
	while (line)
	{
		flag = get_line(&line);
		check_signal(cmdtab);
		if (flag == 1)
			break ;
		else if (flag == 2)
			continue ;
		flag = parse_main(cmdtab, line);
		if (!flag)
			execute_all(cmdtab);
		else
			cmdtab->exit_code = flag;
		add_history(line);
		free(line);
		free_cmds(cmdtab);
		flag = 0;
	}
}

int	main(int ac, char **av, char **ev)
{
	t_cmdtab	*cmdtab;

	(void)av;
	global_signal_manager();
	if (ac != 1)
		return (ft_putendl_fd("\e[1;31mToo many arguments\e[0m\n", 2), 1);
	if (init_cmdtab(&cmdtab, ev))
		return (1);
	main_loop(cmdtab);
	free_cmdtab(cmdtab);
}
