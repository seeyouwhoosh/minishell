/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:51 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/06 20:21:35 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err(void)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (1);
}

int	pwd(t_cmdtab *cmdtab, char **args)
{
	char	*cwd;
	char	path[PATH_MAX];

	if (args && args[1])
		return (err());
	if (cmdtab->cwd)
	{
		ft_putendl_fd(cmdtab->cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(path, PATH_MAX);
	if (!cwd)
		return (error_msg("malloc", NULL, NULL, 1));
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
