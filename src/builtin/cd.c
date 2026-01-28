/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:07 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/28 23:25:53 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *process, char *strerror)
{
	if (!strerror)
		perror(process);
	else
	{
		ft_putstr_fd(process, STDERR_FILENO);
		ft_putstr_fd(":", STDERR_FILENO);
		ft_putendl_fd(strerror, STDERR_FILENO);
	}
	return (1);
}

int		cd(t_cmdtab *cmdtab, char **args)
{
	if (split_len(args) != 2)
		return (error_msg("cd", "too many arguments"));
	if (open(args[1], O_DIRECTORY | O_EXEC))
		return (error_msg("cd", NULL));
	chdir(args[1]);
	free(cmdtab->previous_wd);
	cmdtab->previous_wd = cmdtab->cwd;
	set_env_var(cmdtab, "OLDPWD", cmdtab->previous_wd);
	cmdtab->cwd = ft_strdup(args[1]);
	if (!cmdtab->cwd)
		return (error_msg("malloc", strerror(ENOMEM)));
	set_env_var(cmdtab, "PWD", cmdtab->cwd);
	return (0);
}
