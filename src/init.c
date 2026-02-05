/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/05 23:25:47 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	correct_outfile(t_cmdtab *cmdtab)
{
	size_t	i;

	i = 0;
	while (i < cmdtab->n_cmds)
	{
		cmdtab->cmds[i].outfile = 1;
		i++;
	}
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
