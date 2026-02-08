/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:11:29 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/08 19:13:16 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(const char *filename, int mode)
{
	int	fd;

	fd = -1;
	if (mode == INFILE)
		fd = open(filename, O_RDONLY);
	else if (mode == OUTFILE)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}

static int	create_split(char ***split, char *s)
{
	*split = ft_calloc(2, sizeof(char *));
	if (!(*split))
		return (error_msg("Malloc", NULL, NULL, 1));
	(*split)[0] = s;
	return (SUCCESS);
}

/* Appends s at the end of split */
int	append(char *s, char ***split)
{
	char	**new_split;
	size_t	i;

	if (!(*split))
		return (create_split(split, s));
	i = 0;
	while ((*split)[i])
		i++;
	new_split = ft_calloc(i + 2, sizeof(char *));
	if (!new_split)
		return (error_msg("minishell", "parsing",
				"memory allocation failed", 1));
	i = -1;
	while ((*split)[++i])
		new_split[i] = (*split)[i];
	new_split[i] = s;
	free(*split);
	*split = new_split;
	return (SUCCESS);
}

int	is_delimiter(int c, short squote, short dquote)
{
	if (squote || dquote)
		return (0);
	return (is_whitespace(c) || c == '>' || c == '<' || !c);
}

int	add_to_str(t_cmd *cmd, size_t *i, t_str *str)
{
	if (extend(str))
		return (1);
	str->str[str->len++] = cmd->raw[*i];
	(*i)++;
	return (SUCCESS);
}
