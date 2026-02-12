/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/12 22:11:32 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(t_cmdtab *cmdtab)
{
	size_t	i;

	i = -1;
	if (!cmdtab->cmds)
	{
		cmdtab->n_cmds = 0;
		return ;
	}
	while (cmdtab->n_cmds > ++i)
		free_cmd(cmdtab->cmds + i);
	free(cmdtab->cmds);
	cmdtab->cmds = NULL;
	cmdtab->n_cmds = 0;
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->split_cmd)
		free_split(&(cmd->split_cmd));
	free_pointer(&(cmd->here_doc));
	free_pointer(&(cmd->raw));
	if (cmd->infile)
		close(cmd->infile);
	if (cmd->outfile != 1)
		close(cmd->outfile);
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
	if (!split)
		return ;
	while ((*split)[++i])
		free_pointer(&((*split)[i]));
	free(*split);
	*split = NULL;
}

void	free_cmdtab(t_cmdtab *cmdtab)
{
	if (!cmdtab)
		return ;
	free_split(&(cmdtab->env));
	free_pointer(&(cmdtab->previous_wd));
	free_pointer(&(cmdtab->cwd));
	free_cmds(cmdtab);
	free(cmdtab);
}
