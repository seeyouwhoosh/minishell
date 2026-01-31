/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 10:45:02 by xwu               #+#    #+#             */
/*   Updated: 2026/02/01 00:20:41 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str_cmd, t_cmdtab *cmdtab)
{
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
	if (code < -1)
		return (-1);
	else if (code == CD)
		return (cd(cmdtab, cmd->split_cmd));
	else if (code == CD)
		return (echo(cmdtab, cmd->split_cmd));
	else if (code == CD)
		return (env(cmdtab, cmd->split_cmd));
	else if (code == CD)
		return (ft_exit(cmdtab, cmd->split_cmd));
	else if (code == CD)
		return (export(cmdtab, cmd->split_cmd));
	else if (code == CD)
		return (pwd(cmdtab, cmd->split_cmd));
	else if (code == CD)
		return (unset(cmdtab, cmd->split_cmd));
	else
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
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Command not found\n", 20);
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
		return (error_msg("minishell", NULL, NULL, 127));
	}
	exit = execve(path, split_cmd, cmdtab->env);
	if (exit)
	{
		cmdtab->exit_code = exit;
		free(path);
		error_msg(split_cmd[0], NULL, NULL, exit);
	}
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
	if (fd < 0)
	{
		perror(filename);
		return (EXIT_FAILURE);
	}
	return (fd);
}

/* int	exec_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int		exit;
	int		fd[2];
	pid_t	command;
	size_t	i;

	if (pipe(fd))
		return (error_msg("pipe", NULL, NULL, EPIPE));
	
	i = -1;
	while (cmd->infile[++i])
	{
		cmd->infile[i].fd = ft_open(cmd->infile[i].name, cmd->infile[i].mode);
		if ()
	}
	if (piping_in(cmd));



	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!command)
	{
		exit = exec_builtin(cmd, cmdtab);
		if (exit > -1)
			return (exit);
		else
			exit = exec(cmd->split_cmd, cmdtab);
	}
	else if (command > 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(command, NULL, 0);
	}
} */

/*
		i = -1;
			while (cmd->outfile[++i])
			{
				cmd->outfile[i].fd = ft_open(cmd->outfile[i].name, cmd->outfile[i].mode);
				if (cmd->outfile[i].fd < 0)
					return (error_msg(*(cmd->split_cmd), cmd->outfile[i].name, NULL, 1));
				dup2(cmd->infile[i].fd, STDIN_FILENO);
				close(fd[0]);
*/

int	child_process(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int	exit;
	int	fd[2];

	if (pipe(fd))
		return (error_msg("pipe", NULL, NULL, EPIPE));
	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!command)
	{
		exit = exec_builtin(cmd, cmdtab);
		if (exit < 0)
			exit = exec(cmd->split_cmd, cmdtab);
		return (exit);
	}
	else if (command > 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(command, &exit, 0);
		return (exit);
	}
}

int	multiple_redirections(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int	exit;

	if (pipe(fd))
		return (error_msg("pipe", NULL, NULL, EPIPE));
	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!command)
	{
		exit = exec_builtin(cmd, cmdtab);
		if (exit < 0)
			exit = exec(cmd->split_cmd, cmdtab);
		return (exit);
	}
	else if (command > 0)
		waitpid(command, &exit, 0);
	return (exit);
}
}

int	exec_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	size_t	i;
	size_t	j;
	int		exit;

	i = -1;
	while (cmd->infile[++i])
	{
		cmd->infile[i].fd = ft_open(cmd->infile[i].name, cmd->infile[i].mode);
		if (cmd->infile[i].fd < 0)
			return (error_msg(*(cmd->split_cmd), cmd->infile[i].name, NULL, 1));
		if (dup2(cmd->infile[i].fd, STDIN_FILENO) == -1)
			return (error_msg(*(cmd->split_cmd), NULL, NULL, 1));
		j = -1;
		while (cmd->outfile[++j])
		{
			cmd->outfile[j].fd = ft_open(cmd->outfile[j].name, cmd->outfile[j].mode);
			if (cmd->outfile[j].fd < 0)
				return (error_msg(*(cmd->split_cmd), cmd->outfile[j].name, NULL, 1));
			if (dup2(cmd->outfile[i].fd, STDOU T_FILENO) == -1)
				return (error_msg(*(cmd->split_cmd), NULL, NULL, 1));
			exit = multiple_redirections(cmd, cmdtab);
		}
		child_process(cmd, cmdtab);
	}
}

int	execute(t_cmdtab *cmdtab)
{
	size_t	i;

	i = 0;
	while (cmdtab->n_cmds > i)
		cmdtab->exit_code = exec_cmd(cmdtab->cmds + i++, cmdtab);
	free_cmds(cmdtab);
}




