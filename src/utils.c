/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:20:50 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/05 01:59:01 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_len(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

int	max(int a, int b)
{
	return (a * (a >= b) + b * (b > a));
}

bool	is_whitespace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

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
