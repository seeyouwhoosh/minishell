/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:37 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/31 12:17:41 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err(void)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (1);
}

static int	get_exit_code(char *arg)
{
	int	n;
	int	i;

	n = 0;
	i = -1;
	while (arg[++i])
	{
		if (i == 3)
			return (128);
		n = 10 * n + arg[i] - '0';
	}
	if (n > 255)
		return (128);
	return (n);
}

int	ft_exit(t_cmdtab *cmdtab, char **args)
{
	int	exit_code;

	if (split_len(args) > 2)
		return (err());
	else if (!split_len(args))
		exit_code = cmdtab->exit_code;
	else
		exit_code = get_exit_code(args[1]);
	free_cmdtab(cmdtab);
	exit(exit_code);
}
