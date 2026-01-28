/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:20:50 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/28 21:36:58 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char ***split)
{
	size_t	i;

	i = -1;
	while (split[++i])
		free_pointer(&((*split)[i]));
	free(*split);
	*split = NULL;
}

int	split_len(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

int	max(int a, int b)
{
	return (a * (a >= b) + b * (b > a));
}

void	free_pointer(char **p)
{
	if (*p)
		free(*p);
	*p = NULL;
}

void	free_cmdtab(t_cmdtab *cmdtab) //provisional, probablemente habrá que cambiarlo según se añadan más cosas
{
	if (!cmdtab)
		return ;
	free_pointer(&(cmdtab->env));
	free_pointer(&(cmdtab->previous_wd));
	free_pointer(&(cmdtab->cwd));
	free_cmd(&(cmdtab->cmds));
	free(cmdtab);
}
