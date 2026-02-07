/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:21 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/08 00:40:13 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_cmdtab *cmdtab, char **args)
{
	int	i;

	i = 0;
	if (args && args[1])
		return (error_msg("env", NULL, "too many arguments", 1));
	if (!cmdtab->env)
		return (error_msg("malloc", NULL, NULL, 1));
	while (i < cmdtab->env_len)
		ft_putendl_fd(cmdtab->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
