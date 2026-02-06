/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:04:39 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/06 19:17:11 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we hate linux devs
int	error_msg(char *process, char *details, char *strerror, int error_code)
{
	if (!strerror)
		perror(process);
	else
	{
		ft_putstr_fd(process, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (details)
		{
			ft_putstr_fd(details, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putendl_fd(strerror, STDERR_FILENO);
	}
	return (error_code);
}
