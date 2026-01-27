/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:34:17 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/27 21:18:02 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env(t_cmdtab *cmdtab, char **ev)
{
	int	i;
	int	j;

	cmdtab->env = ft_calloc(sizeof(char *),
			max(1024, split_len(ev)));
	if (!cmdtab->env)
		return (EXIT_FAILURE);
	cmdtab->env_capacity = 1023;
	i = -1;
	while (ev[++i])
	{
		cmdtab->env[i] = ft_strdup(ev[i]);
		if (!cmdtab->env[i])
		{
			free_split(cmdtab->env);
			return (EXIT_FAILURE);
		}
	}
	cmdtab->env_len = i;
	return (EXIT_SUCCESS);
}

bool	is_valid_env_var(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	realloc_env_vars(t_cmdtab *cmdtab)
{
	char	**new_env;
	int		i;

	if (cmdtab->env_capacity == ULONG_MAX)
		return (free_split(cmdtab->env), EXIT_FAILURE);
	if (cmdtab->env_capacity < ULONG_MAX / 2)
		new_env = ft_calloc(2 * cmdtab->env_capacity, sizeof(char *));
	else
		new_env = ft_calloc(1 + cmdtab->env_capacity, sizeof(char *));
	if (!new_env)
		return (free_split(cmdtab->env), EXIT_FAILURE);
	i = 0;
	while (cmdtab->env[i] && i < cmdtab->env_len)
	{
		new_env[i] = cmdtab->env[i];
		i++;
	}
	free_split(cmdtab->env);
	cmdtab->env = new_env;
	return (EXIT_SUCCESS);
}

int	set_env_var(t_cmdtab *cmdtab, char *var, char *val)
{
	size_t	i;
	char	*new_var;
	size_t	pos;
	size_t	len;

	if (cmdtab->env_capacity == cmdtab->env_len && realloc_env_vars(cmdtab))
		return (EXIT_FAILURE);
	new_var = malloc(ft_strlen(var) + 2 + ft_strlen(val));
	if (!new_var)
		return (EXIT_FAILURE);
	i = get_env_ind(cmdtab->env, var);
	if (i == (size_t)(-1))
	{
		i = cmdtab->env_len;
		cmdtab->env_len++;
	}
	else
		free(cmdtab->env[i]);
	pos = ft_strlen(var);
	ft_memcpy(new_var, var, pos);
	new_var[pos++] = '=';
	len = ft_strlen(val);
	ft_memcpy(new_var + pos, val, len);
	new_var[pos + len] = 0;
	cmdtab->env[i] = new_var;
}

size_t	get_env_ind(char **env, char *var)
{
	size_t	i;
	size_t	n;

	n = ft_strlen(var);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(var, env[i], n) && env[i][n] == '=')
			return (i);
	}
	return ((size_t)(-1));
}
