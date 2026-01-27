/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:55 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/27 21:16:02 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(t_cmdtab *cmdtab, char **env, size_t ind)
{
	size_t	i;

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
	int		i;
	size_t	env_ind;
	int		flag;

	i = 1;
	flag = 0;
	while (args[i])
	{
		if (!is_valid_env_var(args[i]) || ft_strchr(args[i], '='))
		{
			if (!flag)
				flag = 1; //propagate the error idk
			flag = 1;
		}
		else
		{
			env_ind = get_env_ind(cmdtab->env, args[i]);
			if (env_ind < (size_t)(-1))
				remove_env_var(cmdtab, cmdtab->env, env_ind);
		}
		i++;
	}
	return (flag);
}
