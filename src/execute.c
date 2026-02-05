/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 10:45:02 by xwu               #+#    #+#             */
/*   Updated: 2026/02/05 01:43:05 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str_cmd, t_cmdtab *cmdtab)
{
	(void)cmdtab;
	if (!strcmp(str_cmd, "cd"))
		return (CD);
	else if (!strcmp(str_cmd, "echo"))
		return (ECHO);
	else if (!strcmp(str_cmd, "env"))
		return (ENV);
	else if (!strcmp(str_cmd, "exit"))
		return (EXIT);
	else if (!strcmp(str_cmd, "export"))
		return (EXPORT);
	else if (!strcmp(str_cmd, "pwd"))
		return (PWD);
	else if (!strcmp(str_cmd, "unset"))
		return (UNSET);
	else
		return (-1);
}

int	exec_builtin(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int	code;

	code = is_builtin(cmd->split_cmd[0], cmdtab);
	if (code == CD)
		return (cd(cmdtab, cmd->split_cmd));
	else if (code == ECHO)
		return (echo(cmdtab, cmd->split_cmd));
	else if (code == ENV)
		return (env(cmdtab, cmd->split_cmd));
	else if (code == EXIT)
		return (ft_exit(cmdtab, cmd->split_cmd));
	else if (code == EXPORT)
		return (export(cmdtab, cmd->split_cmd));
	else if (code == PWD)
		return (pwd(cmdtab, cmd->split_cmd));
	else if (code == UNSET)
		return (unset(cmdtab, cmd->split_cmd));
	return (-1);
}

char	*get_path(char *cmd, char **env)
{
	size_t	i;
	char	**split_paths;
	char	*pathplus;
	char	*path;

	i = -1;
	while (env[++i] && !ft_strnstr(env[i], "PATH=", 5))
		;
	split_paths = ft_split(env[i] + 5, ':');
	if (!split_paths)
		return (NULL);
	i = -1;
	while (split_paths[++i])
	{
		pathplus = ft_strjoin(split_paths[i], "/");
		path = ft_strjoin(pathplus, cmd);
		free(pathplus);
		if (!access(path, X_OK))
			return (ft_freesplit(split_paths), path);
		free(path);
	}
	ft_freesplit(split_paths);
	return (NULL);
}

int	exec(char **split_cmd, t_cmdtab *cmdtab)
{
	char	*path;
	int		exit;

	path = get_path(split_cmd[0], cmdtab->env);
	if (!path)
	{
		ft_freesplit(split_cmd);
		free(path);
		return (error_msg("minishell", split_cmd[0], "Command not found", 127));
	}
	exit = execve(path, split_cmd, cmdtab->env);
	if (exit)
	{
		free(path);
		return (error_msg(split_cmd[0], NULL, NULL, exit));
	}
	return (0);
}

int	ft_open(const char *filename, int mode)
{
	int	fd;

	fd = -1;
	if (mode == INFILE)
		fd = open(filename, O_RDONLY);
	else if (mode == OUTFILE)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}

void	get_line(int fd, char **line, size_t size)
{
	size_t	i;
	int		nread;
	char	c;

	i = 0;
	nread = read(fd, &c, 1);
	while (nread > 0)
	{
		if (i + 1 >= size)
		{
			*line = ft_realloc(*line, size, size * 2);
			size *= 2;
		}
		(*line)[i++] = c;
		if (c == '\n')
			break ;
		nread = read(fd, &c, 1);
	}
	if (nread == -1 || (!nread && !i))
	{
		free(*line);
		*line = NULL;
		return ;
	}
	(*line)[i] = '\0';
}

char	*get_next_line(int fd)
{
	char	*line;
	size_t	size;

	size = 32;
	if (fd < 0)
		return (NULL);
	line = malloc(size);
	if (!line)
		return (NULL);
	get_line(fd, &line, size);
	if (!line)
		return (NULL);
	return (line);
}

void	here_doc_put(char *limiter, size_t n_cmds)
{
	char	*input;
	char	*new_limiter;

	new_limiter = ft_strjoin(limiter, "\n");
	if (!new_limiter)
		return ;
	while (--n_cmds > 0)
		ft_putstr_fd("pipe ", 1);
	ft_putstr_fd("here_doc>", 1);
	input = get_next_line(0);
	while (input)
	{
		if (!ft_strcmp(input, new_limiter))
		{
			free(new_limiter);
			free(input);
			exit(0);
		}
		write(STDOUT_FILENO, input, ft_strlen(input));
		free(input);
		ft_putstr_fd("here_doc>", 1);
		input = get_next_line(0);
	}
}

int	here_doc(char *limiter, size_t n_cmds)
{
	pid_t	read;
	int		fd[2];

	if (pipe(fd))
		return (error_msg("pipe", NULL, NULL, EPIPE));
	read = fork();
	if (read == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!read)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		here_doc_put(limiter, n_cmds);
		return (0);
	}
	else if (read > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(read, NULL, 0);
	}
	return (0);
}

int	open_and_dup(t_file *file, int og_fd)
{
	file->fd = ft_open(file->name, file->mode);
	if (file->fd == -1)
		return (error_msg(file->name, NULL, NULL, 1));
	if (dup2(file->fd, og_fd) == -1)
		return (error_msg("dup2", NULL, NULL, 1));
	close(file->fd);
	return (0);
}

int	exec_last_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int		exit;
	pid_t	command;

	if (cmd->here_doc)
		here_doc(cmd->here_doc, cmdtab->n_cmds);
	else if (cmd->infile.name && open_and_dup(&(cmd->infile), STDIN_FILENO))
		return (1);
	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!command)
	{
		if (cmd->outfile.name && open_and_dup(&(cmd->outfile), STDOUT_FILENO))
			return (1);
		else
			dup2(cmdtab->stdout_fd, STDOUT_FILENO);
		exit = exec_builtin(cmd, cmdtab);
		if (exit < 0)
			exit = exec(cmd->split_cmd, cmdtab);
		return (exit);
	}
	waitpid(command, &exit, 0);
	return (exit);
}

int	child_process(t_cmd *cmd, t_cmdtab *cmdtab, int fd[2])
{
	int	exit;

	if (cmd->outfile.name && open_and_dup(&(cmd->outfile), STDOUT_FILENO))
		return (1);
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	exit = exec_builtin(cmd, cmdtab);
	if (exit < 0)
		exit = exec(cmd->split_cmd, cmdtab);
	return (exit);
}

int	exec_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int		exit;
	int		fd[2];
	pid_t	command;

	if (pipe(fd))
		return (error_msg("pipe", NULL, NULL, EPIPE));
	if (cmd->here_doc && here_doc(cmd->here_doc, cmdtab->n_cmds))
		return (1);
	else if (cmd->infile.name && open_and_dup(&(cmd->infile), STDIN_FILENO))
		return (1);
	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!command)
		exit = child_process(cmd, cmdtab, fd);
	else if (command > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(command, &exit, 0);
	}
	return (exit);
}

int	execute(t_cmdtab *cmdtab)
{
	size_t	i;

	i = 0;
	while (cmdtab->n_cmds > ++i)
		cmdtab->exit_code = exec_cmd(cmdtab->cmds + i - 1, cmdtab);
	cmdtab->exit_code = exec_last_cmd(cmdtab->cmds + i, cmdtab);
	free_cmds(cmdtab);
	return (cmdtab->exit_code);
}
