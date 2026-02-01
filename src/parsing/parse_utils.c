/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/01 20:47:22 by gcassi-d         ###   ########.fr       */
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
