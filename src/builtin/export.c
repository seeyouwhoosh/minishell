/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:43 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/12 21:36:50 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do1(t_cmdtab *cmdtab, char *arg)
{
	char	*middle;

	middle = ft_strchr(arg, '=');
	if (middle)
	{
		*middle = 0;
		if (set_env_var(cmdtab, arg, middle + 1))
			return (error_msg("malloc", NULL, NULL, 1));
	}
	else if (set_env_var(cmdtab, arg, ""))
		return (error_msg("malloc", NULL, NULL, 1));
	return (EXIT_SUCCESS);
}

static void	show(t_cmdtab *cmdtab)
{
	int	i;

	i = 0;
	while (i < cmdtab->env_len)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(cmdtab->env[i], 1);
		i++;
	}
}

int	export(t_cmdtab *cmdtab, char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (split_len(args) == 1)
	{
		show(cmdtab);
		return (0);
	}
	while (args[++i])
	{
		if (!args[i][0] || !is_valid_env_var(args[i]))
		{
			if (!flag)
				return (error_msg("export",
						"not valid in this context", args[i], 1));
			flag = 1;
			continue ;
		}
		if (do1(cmdtab, args[i]))
			return (EXIT_FAILURE);
	}
	return (flag);
}
