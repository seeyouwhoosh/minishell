/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:00:12 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/07 19:44:38 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmds_am(char *line, size_t *holder)
{
	size_t	i;
	short	squote;
	short	dquote;

	squote = 0;
	dquote = 0;
	*holder++;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"' && !squote)
			dquote = 1 - dquote;
		else if (line[i] == '\'' && !dquote)
			squote = 1 - squote;
		else if (!dquote && !squote && line[i] == '|')
			*holder++;
	}
	if (squote)
		return (error_msg("minishell", "parsing",
				"error near unexpected token: `\''", 3));
	if (dquote)
		return (error_msg("minishell", "parsing",
				"error near unexpected token: `\"'", 4));
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
			return (free(str->str), error_msg("minishell", "parsing",
					"memory allocation failed", 1));
		new = ft_calloc(sizeof(char), str->capacity + 2);
		str->capacity += 1;
	}
	if (!new)
		return (free(str->str), error_msg("minishell", "parsing",
				"memory allocation failed", 1));
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
			return (1);
		str->str[str->len++];
	}
	return (SUCCESS);
}

int	add_var(t_why a, t_str *str, size_t *i, short *squote)
{
	t_str	var_name;

	(*i)++;
	if (*squote || (!ft_isalpha(a.cmd->raw[*i]) && a.cmd->raw[*i] != '?'))
	{
		if (extend(str))
			return (1);
		str->str[str->len] = '$';
		str->len++;
		return (SUCCESS);
	}
	if (a.cmd->raw[*i] != '?')
		return (add_exit_code(a, str, (*i)++));
	var_name = new();
	while (ft_isalnum(a.cmd->raw[*i]))
	{
		if (extend(&var_name))
			return (free(str->str), 1);
		var_name.str[var_name.len] = a.cmd->raw[(*i)++];
		var_name.len++;
	}
	return (add(a, str, &var_name));
}
