/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/04 11:28:32 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	all_whitespace(char	*s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s != 32 || (*s < 9 && *s > 13))
			return (0);
		s++;
	}
	return (1);
}

size_t	nth_cmd(char *cmd, size_t n)
{
	size_t	i;
	size_t	pos;
	short	dquote;
	short	squote;

	i = -1;
	dquote = 0;
	squote = 0;
	pos = 0;
	while (i < n)
	{
		if (cmd[pos] == '\"' && !squote)
			dquote = 1 - dquote;
		else if (cmd[pos] == '\'' && !dquote)
			squote = 1 - squote;
		else if (!dquote && !squote && cmd[pos] == '|')
			i++;
		pos++;
	}
	return (pos);
}

/* Counts the number of commands in a line, taking into account
double and single quotes, returns 0 if there are unmatched single or double quotes */
size_t	n_cmds(char *line)
{
	size_t	i;
	short	squote;
	short	dquote;
	size_t	count;

	squote = 0;
	dquote = 0;
	count = 0;
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
	return (count + 1);
}

int	add_squote(t_cmd *cmd_ui, char *cmd, size_t *pos, size_t ind)
{
	char	*token;
	size_t	i;

	i = 0;
	while (cmd[*pos + ++i] != '\'')
		;
	token = ft_calloc(sizeof(char), i);
	if (!token)
		return (MALLOC);
	ft_memcpy(token, cmd + *pos + 1, i - 1);
	cmd_ui->split_cmd[ind] = token;
	*pos += i;
	return (SUCCESS);
}

int	add_dquote(t_cmd *cmd_ui, char *cmd, size_t *pos, size_t ind)
{
	char	*token;
	size_t	i;

	i = 0;
	while (cmd[*pos + ++i] != '\'')
		;
	token = ft_calloc(sizeof(char), i);
	if (!token)
		return (MALLOC);
	ft_memcpy(token, cmd + *pos + 1, i - 1);
	cmd_ui->split_cmd[ind] = token;
	*pos += i;
	return (SUCCESS);
}

int	is_delimiter(int c)
{
	return (is_whitespace(c) || c == '>' || c == '<' || c == '|' || !c);
}

int	extend(t_str *str)
{
	char	*new;

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

char	*get_next_command(t_cmd *cmd, char *pos, size_t ind, t_str str)
{
	while (*pos != '|' && *pos)
	{
		if (str.len == str.capacity)
		{
			if (extend(&str))
			{
				cmd[ind].raw = NULL;
				return (NULL);
			}
		}
		str.str[str.len] = *pos;
		str.len++;
		pos++;
	}
	cmd[ind].raw = str.str;
	if (*pos == '|')
		pos++;
	return (pos);
}

static t_str	new()
{
	t_str	new;

	new.capacity = 100;
	new.len = 0;
	new.str = ft_calloc(sizeof(char), 100);
	return (new);
}

static void	free_raws(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i].raw)
	{
		free(cmd[i].raw);
		cmd[i].raw = NULL;
	}
}

int	get_commands(t_cmd *cmd, char *str)
{
	t_str	current;
	size_t	i;

	i = 0;
	while (is_whitespace(*str))
		str++;
	while (*str)
	{
		current = new();
		if (!current.str)
			return (free_raws(cmd), MALLOC);
		str = get_next_command(cmd, str, i, current);
		if (!str)
			return (free_raws(cmd), MALLOC);
		i++;
		while (is_whitespace(*str))
			str++;
	}
	return (SUCCESS);
}
