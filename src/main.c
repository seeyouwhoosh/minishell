/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/12 22:33:29 by xwu              ###   ########.fr       */
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
		check_signal(cmdtab);
		flag = get_line(&line);
		if (flag == 1)
			break ;
		else if (flag == 1)
			continue ;
		flag = parse_main(cmdtab, line);
		if (!flag)
			execute_all(cmdtab);
		else
			cmdtab->exit_code = flag;
		add_history(line);
		free(line);
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
		return (free(cmdtab), 1);
	main_loop(cmdtab);
	free_cmdtab(cmdtab);
}
