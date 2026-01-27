/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 20:20:50 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/27 20:26:36 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	size_t	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

size_t	split_len(char **split)
{
	size_t	i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

size_t	max(size_t a, size_t b)
{
	return (a * (a >= b) + b * (b > a));
}
