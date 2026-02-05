/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/04 02:25:56 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	cmd->split_cmd = NULL;
	cmd->here_doc = NULL;
	cmd->infile.name = NULL;
	cmd->infile.fd = STDIN_FILENO;
	cmd->infile.mode = OUTFILE;
	cmd->outfile.name = NULL;
	cmd->outfile.fd = STDOUT_FILENO;
}

int	init_cmdtab(t_cmdtab *cmdtab, char **ev)
{
	char	path[PATH_MAX];

	cmdtab = malloc(sizeof(cmdtab));
	if (!cmdtab)
		return (1);
	if (copy_env(cmdtab, ev))
		return (free_cmdtab(cmdtab), 1);
	cmdtab->stdout_fd = dup(STDOUT_FILENO);
	cmdtab->cwd = getcwd(path, PATH_MAX);
	if (!cmdtab->cwd)
		return (error_msg("malloc", NULL, NULL, 1));
	cmdtab->previous_wd = strdup("");
	if (!cmdtab->previous_wd)
		return (error_msg("malloc", NULL, NULL, 1));
}
