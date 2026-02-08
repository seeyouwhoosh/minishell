/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:43:07 by xwu               #+#    #+#             */
/*   Updated: 2026/02/08 19:49:52 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup(int new_fd, int og_fd)
{
	if (dup2(new_fd, og_fd) == -1)
		return (error_msg("dup2", NULL, NULL, 1));
	return (0);
}

int	manage_infile(t_cmd *cmd, t_cmdtab *cmdtab)
{
	if (cmd->here_doc && here_doc(cmd->here_doc, cmdtab->n_cmds))
		return (1);
	if (cmd->infile && (cmd->last != INFILE)
		&& ft_dup(cmd->infile, STDIN_FILENO))
		return (1);
	return (0);
}

int	manage_outfile(t_cmd *cmd, t_cmdtab *cmdtab)
{
	if (cmd->outfile != 1 && ft_dup(cmd->outfile, STDOUT_FILENO))
		return (1);
	else if (ft_dup(cmdtab->stdout_fd, STDOUT_FILENO))
		return (1);
	return (0);
}

/* In case there is no command, just rediretion */
int	just_redirection(t_cmd *cmd)
{
	if (!cmd->split_cmd)
	{
		ft_putendl_fd(0, 1);
		return (1);
	}
	return (0);
}
