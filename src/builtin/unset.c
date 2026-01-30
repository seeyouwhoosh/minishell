/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:55 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/30 19:57:00 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_cmdtab *cmdtab, char **env, int ind)
{
	int	i;

	free(env[ind]);
	i = ind;
	while (++i <= cmdtab->env_len)
	{
		env[ind] = env[i];
		ind++;
	}
	cmdtab->env_len--;
}

int	unset(t_cmdtab *cmdtab, char **args)
{
	int	i;
	int	env_ind;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i])
	{
		if ((!is_valid_env_var(args[i]) || ft_strchr(args[i], '=')) && !flag)
		{
			flag = 1;
			error_msg("unset", args[i], "invalid parameter name", 1);
		}
		else
		{
			env_ind = get_env_ind(cmdtab, cmdtab->env, args[i]);
			if (env_ind > -1)
				remove_env_var(cmdtab, cmdtab->env, env_ind);
		}
		i++;
	}
	return (flag);
}
