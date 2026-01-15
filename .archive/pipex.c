/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:30:34 by xwu               #+#    #+#             */
/*   Updated: 2025/11/09 22:24:23 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char *cmd, char **env)
{
	int		fd[2];
	pid_t	command;

	if (pipe(fd))
		return (perror("Pipe failed"));
	command = fork();
	if (command == -1)
		return (perror("Fork failed"));
	if (!command)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		exec(cmd, env);
	}
	else if (command > 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(command, NULL, 0);
	}
}

void	here_doc(char *limiter)
{
	pid_t	read;
	int		fd[2];

	if (pipe(fd))
		return (perror("Pipe failed"));
	read = fork();
	if (!read)
	{
		close(fd[0]);
		here_doc_put(limiter, fd[1]);
		dup2(fd[1], STDOUT_FILENO);
	}
	else if (read > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(read, NULL, 0);
	}
}

void	error(void)
{
	char	*msg;

	msg = "pipex simulates the following:\n\t\033[1m< infile cmd1\
 | cmd2 | ... | cmdn > outfile\033[0m\n\
Correct usage:\033[1m ./pipex infile cmd1 cmd2 ... cmdn outfile\033[0m\n\
\t\033[1m<< LIMITER cmd1 | cmd2 | ... | cmdn >> outfile\033[0m\n\
Correct usage:\033[1m ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn \
outfile\033[0m\n";
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

int	ft_open(const char *filename, char mode)
{
	int	fd;

	fd = -1;
	if (mode == 'r')
		fd = open(filename, O_RDONLY);
	else if (mode == 'w')
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 'a')
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		perror(filename);
		exit (EXIT_FAILURE);
	}
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	outfile;
	int	infile;

	if (ac < 5)
		error();
	if (!(strcmp(av[1], "here_doc")))
	{
		if (ac < 6)
			error();
		i = 2;
		outfile = ft_open(av[ac - 1], 'a');
		here_doc(av[2]);
	}
	else
	{
		i = 1;
		outfile = ft_open(av[ac - 1], 'w');
		infile = ft_open(av[1], 'r');
		dup2(infile, STDIN_FILENO);
	}
	while (++i < ac - 2)
		child_process(av[i], env);
	dup2(outfile, STDOUT_FILENO);
	exec(av[ac - 2], env);
}
