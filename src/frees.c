/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/01/28 20:34:28 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(t_cmdtab *cmdtab)
{
	size_t	i;

	i = -1;
	while (cmdtab->cmds[++i].split_cmd)
	{
		free_cmd(cmdtab->cmds + i);
		free(cmdtab->cmds + i);
	}
	cmdtab->cmds = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->split_cmd)
		ft_freesplit(cmd->split_cmd);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->errfile)
		free(cmd->errfile);
}

void	free_pointer(char **p)
{
	if (*p)
		free(*p);
	*p = NULL;
}

void	free_split(char ***split)
{
	size_t	i;

	i = -1;
	while (split[++i])
		free_pointer(&((*split)[i]));
	free(*split);
	*split = NULL;
}
