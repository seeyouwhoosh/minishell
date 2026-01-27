/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:43 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/27 21:39:28 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	propagate(char	*arg)
{
	if (!arg[0]) //yes, empty string gives a different message
		//message: export: not valid in this context:
		;
	else
		//message: not an identifier: <val>
		;
	//I think there are more, for cases in which arg[0] == '='
}

static int	do1(t_cmdtab *cmdtab, char *arg)
{
	char	*middle;

	middle = ft_strchr(arg, '=');
	if (middle)
	{
		*middle = 0;
		if (set_env_var(cmdtab, arg, middle + 1))
			return (EXIT_FAILURE);
	}
	else if (set_env_var(cmdtab, arg, middle + 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	export(t_cmdtab *cmdtab, char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (++i)
	{
		if (!args[i][0] || !is_valid_env_var(args[i]))
		{
			if (!flag)
				propagate(args[i]);
			flag = 1;
			continue ;
		}
		if (do1(cmdtab, args[i]))
			; //some malloc fail;	
	}
	return (flag);
}
