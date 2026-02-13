/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:04:39 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/12 23:17:17 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmdtab(t_cmdtab **cmdtab, char **ev)
{
	*cmdtab = ft_calloc(1, sizeof(t_cmdtab));
	if (!(*cmdtab))
		return (1);
	if (copy_env(*cmdtab, ev))
		return (free_cmdtab(*cmdtab), 1);
	(*cmdtab)->stdout_fd = dup(STDOUT_FILENO);
	(*cmdtab)->stdin_fd = dup(STDIN_FILENO);
	(*cmdtab)->cwd = getcwd(NULL, 0);
	if (!(*cmdtab)->cwd)
		return (free_cmdtab(cmdtab), error_msg("malloc", NULL, NULL, 1));
	(*cmdtab)->previous_wd = strdup("");
	if (!(*cmdtab)->previous_wd)
		return (free_cmdtab(cmdtab), error_msg("malloc", NULL, NULL, 1));
	return (0);
}

int	get_line(char **line)
{
	*line = readline("Minishell> ");
	if (!(*line))
		return (1);
	rl_on_new_line();
	if (all_whitespace(*line))
		return (free(*line), 2);
	return (0);
}

/* we hate linux devs */
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
