/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:50:45 by xwu               #+#    #+#             */
/*   Updated: 2026/02/12 20:42:58 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	eof_warning_message(int nline, char *limiter)
{
	ft_putstr_fd("\nwarning: here-document at line ", 1);
	ft_putstr_fd(ft_itoa(nline), 1);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 1);
	ft_putstr_fd(limiter, 1);
	ft_putstr_fd("')\n", 1);
}

void	put_heredoc_prompt(size_t n_cmds)
{
	while (--n_cmds > 0)
		ft_putstr_fd("pipe ", 1);
	ft_putstr_fd("here_doc> ", 1);
}

void	here_doc_put(char *limiter, size_t n_cmds, int fd)
{
	char	*input;
	char	*new_limiter;
	int		nline;

	new_limiter = ft_strjoin(limiter, "\n");
	if (!new_limiter)
		return ;
	put_heredoc_prompt(n_cmds);
	input = get_next_line(0);
	nline = 0;
	while (input)
	{
		if (!ft_strcmp(input, new_limiter))
		{
			free(new_limiter);
			free(input);
			return ;
		}
		ft_putstr_fd(input, fd);
		free(input);
		put_heredoc_prompt(n_cmds);
		input = get_next_line(0);
		nline++;
	}
	return (eof_warning_message(nline, limiter));
}

int	here_doc(char *limiter, size_t n_cmds)
{
	pid_t	read;
	int		fd[2];
	int		status;

	parent_signal_manager();
	if (pipe(fd))
		return (-error_msg("pipe", NULL, NULL, errno));
	read = fork();
	if (read == -1)
		return (-error_msg("fork", NULL, NULL, errno));
	if (!read)
	{
		child_signal_manager();
		close(fd[0]);
		here_doc_put(limiter, n_cmds, fd[1]);
		if (ft_dup(fd[1], STDOUT_FILENO))
			exit(1);
		exit(0);
	}
	close(fd[1]);
	waitpid(read, &status, 0);
	global_signal_manager();
	if (which_exit(status))
		return (-which_exit(status));
	return (fd[0]);
}

int	manage_heredoc(t_cmdtab *cmdtab)
{
	size_t	i;
	int		new_input;

	i = -1;
	while (cmdtab->n_cmds > ++i)
	{
		if (cmdtab->cmds[i].here_doc)
		{
			new_input = here_doc(cmdtab->cmds[i].here_doc,
					cmdtab->n_cmds);
			if (new_input < 0)
				return (new_input);
			if (!cmdtab->cmds[i].infile)
				cmdtab->cmds[i].infile = new_input;
			else
				close(new_input);
		}
	}
	return (0);
}

