/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:07 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/07 16:55:03 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err(char *dir)
{
	perror("cd");
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(dir, STDERR_FILENO);
	return (1);
}

int	cd(t_cmdtab *cmdtab, char **args)
{
	if (split_len(args) != 2)
		return (error_msg("cd", NULL, "too many arguments", 1));
	if (open(args[1], O_DIRECTORY | O_EXCL))
		return (err(args[1]));
	chdir(args[1]);
	if (cmdtab->previous_wd)
		free(cmdtab->previous_wd);
	cmdtab->previous_wd = cmdtab->cwd;
	set_env_var(cmdtab, "OLDPWD", cmdtab->previous_wd);
	cmdtab->cwd = ft_strdup(args[1]);
	if (!cmdtab->cwd)
		return (error_msg("malloc", NULL, NULL, 1));
	set_env_var(cmdtab, "PWD", cmdtab->cwd);
	return (0);
}
