/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:10:31 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/06 20:06:22 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isnflag(char *arg)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	if (arg[i] != '-')
		return (false);
	i++;
	while (arg[i] && arg[i] == 'n')
	{
		flag = true;
		i++;
	}
	if (arg[i])
		flag = false;
	return (flag);
}

int	echo(t_cmdtab *cmdtab, char **args)
{
	int		i;
	bool	flag;

	(void)cmdtab;
	i = 1;
	while (args[i] && isnflag(args[i]))
	{
		flag = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd(1, '\n');
	return (EXIT_SUCCESS);
}
