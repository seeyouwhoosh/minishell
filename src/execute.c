/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 10:45:02 by xwu               #+#    #+#             */
/*   Updated: 2026/01/31 13:18:48 by xwu              ###   ########.fr       */
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

int	piping(t_cmd *cmd)
{
	if (cmd->infile)
	if (cmd->outfile)
	if (cmd->infile)
	;
}

int	exec_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int		exit;
	int		fd[2];
	pid_t	command;

	if (pipe(fd))
		return (error_msg("pipe", NULL, NULL, EPIPE));
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
}

int	execute(t_cmdtab *cmdtab)
{
	size_t	i;

	i = 0;
	while (cmdtab->n_cmds > i)
		cmdtab->exit_code = exec_cmd(cmdtab->cmds + i++, cmdtab);
	free_cmds(cmdtab);
}




