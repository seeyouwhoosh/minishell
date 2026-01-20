/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:50:04 by xwu               #+#    #+#             */
/*   Updated: 2025/10/31 11:50:04 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft_utils.c"
#include "pipex_utils.c"

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

void	int_signal(int n)
{
	(void)n;
	signal(SIGINT, SIG_IGN);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGINT, int_signal);
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
	split_paths = ft_split(env[i] + 5, ":");
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

void	exec(char *cmd, char **env)
{
	char	*path;
	char	**split_cmd;

	split_cmd = ft_split(cmd, " \t");
	path = get_path(split_cmd[0], env);
	if (!path)
	{
		ft_freesplit(split_cmd);
		free(path);
		return ;
	}
	if (execve(path, split_cmd, env))
	{
		perror(path);
		ft_freesplit(split_cmd);
		free(path);
	}
}

int	process_args(char *line, char **env)
{
	char		**tokens;
	int			pid;
	t_cmdtab	cmdtab;
	t_cmd		cmds;
	size_t		i;
	char		*arg;
	char		*temp;
	char		*temp2;

	cmdtab.cmds = &cmds;
	tokens = ft_split(line, " \t");
	i = -1;
	while (tokens[i])
	{
		if (charset_in_str(tokens[i], "><"))
		{
			if (!ft_strcmp(tokens[i], "<<"))
				here_doc(tokens [i + 1]);
			else if (!ft_strcmp(tokens[i], "<"))
				cmdtab.infile = ft_open(tokens[i + 1], 'r');
			else if (!ft_strcmp(tokens[i], ">>"))
				cmdtab.outfile = ft_open(tokens[i + 1], 'a');
			else if (!ft_strcmp(tokens[i], ">"))
				cmdtab.outfile = ft_open(tokens[i + 1], 'w');
		}
		else
		{
			if (!access(tokens[i], X_OK))
				cmdtab.cmds->cmd = tokens[i++];
			
			arg = NULL;
			while (charset_in_str(tokens[i], "|;"))
			{
				temp = arg;
				arg = ft_strjoin(arg, tokens[i]);
				free(temp);
				temp2 = arg;
				arg = ft_strjoin(tokens[i], " ");
				free(temp2);
				i++;
			}
			cmdtab.cmds->args = arg;
		}
		i++;
	}
	line = ft_strjoin(cmdtab.cmds->cmd, " ");
	line = ft_strjoin(cmdtab.cmds->cmd, cmdtab.cmds->args);
	pid = fork();
	if (!pid)
	{
		exec(line, env);
		exit(0);
	}
	wait(NULL);
	write(1, "Finished\n", 9);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	(void)env;
	if (ac != 1)
		return(write(1, "\e[1;31mInvalid arguments\e[0m\n", 29));
	signal(SIGINT, int_signal);
	signal(SIGQUIT, SIG_IGN);
	line = (char *)1;
	while (line)
	{
		line = readline("Minishell> ");
		rl_on_new_line();
		if (all_whitespace(line))
			continue ;
		process_args(line, env);
		add_history(line);
		free(line);
	}
}