/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:04:39 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/28 21:37:36 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd **cmd)
{
	if (!*cmd)
		return ;
	free_split(&((*cmd)->split_cmd));
	free(*cmd);
	*cmd = NULL;
}

int	error_msg(char *process, char *strerror)
{
	if (!strerror)
		perror(process);
	else
	{
		ft_putstr_fd(process, STDERR_FILENO);
		ft_putstr_fd(":", STDERR_FILENO);
		ft_putendl_fd(strerror, STDERR_FILENO);
	}
	return (1);
}
