/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:05:48 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/05 01:36:01 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//orden pensado: heredoc, variables, redirecciones, do it
int	parse_command(t_cmd *cmd)
{
	;
}

//orden: pipes, tokens, locate redirections, env_vars
int	parse_main(t_cmdtab *cmdtab, char *cmd)
{
	size_t	i;
	int		flag;

	flag = cmds_am(cmd, &(cmdtab->n_cmds));
	if (flag)
		return (free(cmd), flag);
	cmdtab->cmds = ft_calloc(cmdtab->n_cmds + 1, sizeof(t_cmd));
	if (!cmdtab->cmds)
		return (free(cmd), MALLOC);
	flag = create_raws(cmdtab->cmds, cmd);
	if (flag)
		return (free(cmd), flag);
	flag = get_commands(cmdtab->cmds, cmd);
	if (flag)
		return (free(cmd), flag);
	i = -1;
	while (++i < cmdtab->n_cmds)
	{
		flag = parse_command(cmdtab->cmds + i);
		if (flag)
			return (free(cmd), flag);
	}
	return (free(cmd), SUCCESS);
}
