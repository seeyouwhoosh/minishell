/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:00:12 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/04 22:21:36 by gcassi-d         ###   ########.fr       */
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
	if (str->capacity < ULONG_MAX / 2)
	{
		new = ft_calloc(sizeof(char), str->capacity * 2);
		str->capacity *= 2;
	}
	else
	{
		if (str->capacity == ULONG_MAX)
			return (free(str->str), MALLOC);
		new = ft_calloc(sizeof(char), str->capacity + 1);
		str->capacity += 1;
	}
	if (!new)
		return (free(str->str), MALLOC);
	ft_memcpy(new, str->str, str->len);
	free(str->str);
	str->str = new;
	return (SUCCESS);
}

