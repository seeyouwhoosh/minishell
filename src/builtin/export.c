/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:43 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/27 21:31:47 by gcassi-d         ###   ########.fr       */
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

int	export(t_cmdtab *cmdtab, char **args)
{
	int		i;
	char	*middle;
	int		flag;

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
		middle = ft_strchr(args[i], '=');
		if (middle)
		{
			*middle = 0;
			set_env_var(cmdtab, args[i], middle + 1);
		}
		else
			set_env_var(cmdtab, args[i], "");
	}
	return (flag);
}
