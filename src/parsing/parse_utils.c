/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/09 20:41:06 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quotes(int pos, short *squote, short *dquote)
{
	if (!*squote && pos == '\"')
		*dquote = 1 - *dquote;
	if (!*dquote && pos == '\'')
		*squote = 1 - *squote;
}

char	*get_next_command(t_cmd *cmd, char *pos, size_t ind, t_str str)
{
	short	squote;
	short	dquote;

	squote = 0;
	dquote = 0;
	while ((*pos != '|' || (squote || dquote)) && *pos)
	{
		if (extend(&str))
		{
			cmd[ind].raw = NULL;
			return (NULL);
		}
		quotes(*pos, &squote, &dquote);
		str.str[str.len] = *pos;
		str.len++;
		pos++;
	}
	cmd[ind].raw = str.str;
	if (*pos == '|')
		pos++;
	return (pos);
}

t_str	new(void)
{
	t_str	new;

	new.capacity = 100;
	new.len = 0;
	new.str = ft_calloc(sizeof(char), 101);
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

int	get_commands(t_cmd *cmd, char *str, size_t max)
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
			return (free_raws(cmd), error_msg("mnsh", NULL,
					"memory allocation failed", 1));
		str = get_next_command(cmd, str, i, current);
		if (!str)
			return (free_raws(cmd), 1);
		i++;
		while (is_whitespace(*str))
			str++;
	}
	if (check_rest(cmd, i, max))
		return (error_msg("mnsh", NULL,
				"memory allocation failed", 1));
	return (SUCCESS);
}
