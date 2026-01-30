/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/01/28 20:34:28 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Find match. Returns match; if not match, returns itself */
char	*matched_quote(char *line)
{
	size_t	i;

	i = 1;
	while (line[i] && line[i] != line[0])
		i++;
	if (!line[i])
		return (line);
	return (line + i);
}

void	create_split(char ***split, char *s)
{
	*split = malloc(2 * sizeof(char *));
	if (!(*split))
		return ;
	(*split)[0] = ft_strdup(s);
	(*split)[1] = NULL;
}

/* Appends s at the end of split */
void	append(char ***split, char *s)
{
	char	**old_split;
	char	**new_split;
	size_t	i;

	if (!split || !s)
		return ;
	old_split = *split;
	if (!old_split)
		return (create_split(split, s));
	i = 0;
	while (old_split[i])
		i++;
	new_split = malloc((i + 2) * sizeof(char *));
	if (!new_split)
		return ;
	i = -1;
	while (old_split[++i])
		new_split[i] = ft_strdup(old_split[i]);
	new_split[i] = ft_strdup(s);
	new_split[i + 1] = NULL;
	ft_freesplit(old_split);
	*split = new_split;
}

/* Splits s and appends each token of s into split */
void	split_and_append(char *s, char ***split)
{
	char	**tmp;
	size_t	i;

	tmp = ft_split_charset(s, TOKEN_DELIMITER);
	i = 0;
	while (tmp[i])
		append(split, tmp[i++]);
	ft_freesplit(tmp);
}

/* Counts the number of commands in a line, taking into account
double and single quotes */
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
		if (line[i] == '\"')
			dquote = (dquote + 1) % 2;
		if (line[i] == '\'')
			squote = (squote + 1) % 2;
		else if ((!dquote || !squote) && line[i] == '|')
			count++;
	}
	return (count + 1);
}
