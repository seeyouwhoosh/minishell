/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:21 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/30 19:36:37 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err(void)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (1);
}

int	env(t_cmdtab *cmdtab, char **args)
{
	int	i;

	i = 0;
	if (args && args[1])
		return (err());
	if (!cmdtab->env)
		return (error_msg("malloc", NULL, NULL, 1));
	while (cmdtab->env[i])
		ft_putendl_fd(cmdtab->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
