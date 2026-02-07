/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:07 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/07 19:37:24 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	err(void)
{
	perror("cd");
	return (errno);
}

static int	go_to_home(t_cmdtab *cmdtab)
{
	char	*home_dir;

	home_dir = get_env_val(cmdtab, cmdtab->env, "HOME");
	if (!home_dir)
		return (error_msg("malloc", NULL, NULL, ENOMEM));
	chdir(home_dir);
	free(home_dir);
	return (0);
}

static int	change_wd_env(t_cmdtab *cmdtab, char *wd)
{
	if (cmdtab->previous_wd)
		free(cmdtab->previous_wd);
	cmdtab->previous_wd = cmdtab->cwd;
	set_env_var(cmdtab, "OLDPWD", cmdtab->previous_wd);
	if (!wd)
		cmdtab->cwd = get_env_val(cmdtab, cmdtab->env, "HOME");
	else
		cmdtab->cwd = ft_strdup(wd);
	if (!cmdtab->cwd)
		return (error_msg("malloc", NULL, NULL, 1));
	set_env_var(cmdtab, "PWD", cmdtab->cwd);
	return (0);
}

static int	go_to_arg(char *wd)
{
	if (!opendir(wd))
		return (err());
	if (chdir(wd) == -1)
		return (err());
	return (0);
}

int	cd(t_cmdtab *cmdtab, char **args)
{
	int	ext;

	if (split_len(args) != 2)
		return (error_msg("cd", NULL, "too many arguments", 1));
	if (!args[1])
		ext = go_to_home(cmdtab);
	else
		ext = go_to_arg(args[1]);
	if (ext)
		return (errno);
	change_wd_env(cmdtab, args[1]);
	return (0);
}
