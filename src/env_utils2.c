/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:04:18 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/28 22:09:06 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_val(t_cmdtab *cmdtab, char **env, char *var)
{
	int	i;
	int	n;

	n = ft_strlen(var);
	i = -1;
	while (++i < cmdtab->env_len)
	{
		if (!ft_strncmp(var, env[i], n) && env[i][n] == '=')
			return (*env + n + 1); //devuelve un puntero no copiado, no debería de haber problemas porque no es algo que se vaya a modificar en parsing, sólo en export
	}
	return (NULL);
}