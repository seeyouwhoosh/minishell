/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:21 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/17 21:27:26 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_cmdtab *cmdtab, char **args)
{
	int	i;

	i = 0;
	if (args && args[1])
	{
		//propagate de error idk
		return (EXIT_FAILURE);
	}
	if (!cmdtab->env)
		return (EXIT_FAILURE);
	while (cmdtab->env[i])
		ft_putendl_fd(cmdtab->env[i], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
