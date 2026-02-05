/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:00:12 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/06 00:25:06 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Counts the number of commands in a line, taking into account
double and single quotes, returns 0 if there are unmatched
single or double quotes */
size_t	n_cmds(char *line)
{
	size_t	i;
	short	squote;
	short	dquote;
	size_t	count;

	squote = 0;
	dquote = 0;
	count = 1;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"' && !squote)
			dquote = 1 - dquote;
		else if (line[i] == '\'' && !dquote)
			squote = 1 - squote;
		else if (!dquote && !squote && line[i] == '|')
			count++;
	}
	if (squote || dquote)
		return (0);
	return (count);
}

int	cmds_am(char *line, size_t *holder)
{
	size_t	i;
	short	squote;
	short	dquote;
	size_t	count;

	squote = 0;
	dquote = 0;
	count = 1;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"' && !squote)
			dquote = 1 - dquote;
		else if (line[i] == '\'' && !dquote)
			squote = 1 - squote;
		else if (!dquote && !squote && line[i] == '|')
			count++;
	}
	if (squote)
		return (MISMATCHED_SQUOTE);
	if (dquote)
		return (MISMATCHED_DQUOTE);
	*holder = count;
	return (SUCCESS);
}

int	extend(t_str *str)
{
	char	*new;

	if (str->capacity != str->len)
		return (SUCCESS);
	if (str->capacity < (ULONG_MAX - 1) / 2)
	{
		new = ft_calloc(sizeof(char), str->capacity * 2 + 1);
		str->capacity *= 2;
	}
	else
	{
		if (str->capacity == ULONG_MAX - 1)
			return (free(str->str), MALLOC);
		new = ft_calloc(sizeof(char), str->capacity + 2);
		str->capacity += 1;
	}
	if (!new)
		return (free(str->str), MALLOC);
	ft_memcpy(new, str->str, str->len);
	free(str->str);
	str->str = new;
	return (SUCCESS);
}

static int	add(t_why a, t_str *str, t_str *var_name)
{
	char	*val;

	val = get_env_val(a.cmdtab, a.cmdtab->env, var_name->str);
	free(var_name->str);
	while (*val)
	{
		if (extend(str))
			return (MALLOC);
		str->str[str->len++];
	}
	return (SUCCESS);
}

int	add_var(t_why a, t_str *str, size_t *i, short *squote)
{
	t_str	var_name;

	(*i)++;
	if (!*squote || (!ft_isalpha(a.cmd->raw[*i]) && a.cmd->raw[*i] != '?'))
	{
		if (expand(str))
			return (MALLOC);
		str->str[str->len] = '$';
		str->len++;
		return (SUCCESS);
	}
	if (a.cmd->raw[*i] != '?')
		return (add_exit_code(a, str, (*i)++));
	var_name = new();
	while (ft_isalnum(a.cmd->raw[*i]))
	{

		if (expand(&var_name))
			return (free(str->str), MALLOC);
		var_name.str[var_name.len] = a.cmd->raw[(*i)++];
		str->len++;
	}
	return (add(a, str, &var_name));
}
