/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:08:41 by xwu               #+#    #+#             */
/*   Updated: 2026/01/20 22:29:15 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_var(char *var, char **ev)
{
	size_t	i;
	char	*new_var;

	new_var = ft_strjoin(var, "=");
	i = -1;
	while (ev[++i])
	{
		if (!ft_strncmp(ev[i], new_var, ft_strlen(new_var)))
		{
			free(new_var);
			return (ev[i] + i + 1);
		}
	}
	free(new_var);
	return ("");
}

char	*next_word(char *line)
{
	char	*word;
	size_t	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, line, i);
	word[i] = 0;
	return (word);
}

int	insert_var(char **line, char *var, size_t n, char **ev)
{
	char	*new;
	size_t	ll;
	size_t	lv;
	char	*tmp;
	char	*expanded;

	expanded = search_var(var, ev);
	tmp = *line;
	ll = ft_strlen(*line);
	lv = ft_strlen(expanded);
	new = malloc(ll + lv + 1);
	if (!new)
		return (0);
	ft_memcpy(new, *line, n);
	ft_memcpy(new + n, expanded, lv);
	ft_memcpy(new + n + lv, *line + n + ft_strlen(var), ll - n - ft_strlen(var) - 1);
	new[ll + lv] = 0;
	free(tmp);
	*line = new;
	return (lv);
}

int	variable_expansion(char **line, char **ev)
{
	short	dquote;
	size_t	i;
	char	*var;

	i = 0;
	dquote = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'')
			dquote = (dquote + 1) % 2;
		else if ((*line)[i] == '$' && !dquote)
		{
			var = next_word(*line + i + 1);
			if (!var)
				return (1);
			i += insert_var(line, var, i, ev);
			free(var);
		}
		i++;
	}
	return (0);
}
