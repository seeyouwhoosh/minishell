/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:51 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/08 00:41:27 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_cmdtab *cmdtab, char **args)
{
	char	*cwd;
	char	path[PATH_MAX];

	if (args && args[1])
		return (error_msg("pwd", NULL, "too many arguments", 1));
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
