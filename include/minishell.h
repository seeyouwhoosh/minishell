/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:46:16 by xwu               #+#    #+#             */
/*   Updated: 2026/02/01 17:44:26 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include <string.h>
# include <errno.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef TOKEN_DELIMITER
#  define TOKEN_DELIMITER " \t\r\n\a"
# endif

typedef struct s_cmds
{
	char	**split_cmd;
	t_file	infile; //cat < a <c
	t_file	outfile;
	char	*here_doc;
}			t_cmd;

typedef struct s_file
{
	char	*name;
	int		fd;
	int		mode;
}			t_file;

typedef struct s_cmdtab
{
	t_cmd	*cmds;
	size_t	n_cmds;
	char	*cwd;
	char	*previous_wd;
	char	**env;
	int		env_capacity;
	int		env_len;
	int		exit_code;
	char	**history;
}			t_cmdtab;

enum
{
	NO_REDIR,
	INFILE,
	OUTFILE,
	HERE_DOC,
	APPEND
};

enum
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
};

/* INITS */
int		init_cmd(t_cmd *cmd, t_cmdtab *cmdtab);

/* FREES */
void	free_split(char ***split);
void	free_pointer(char **p);
void	free_cmdtab(t_cmdtab *cmdtab);
void	free_cmd(t_cmd *cmd);
void	free_cmds(t_cmdtab *cmdtab);

/* VARIABLE EXPANSION */
size_t	n_cmds(char *line);
char	*search_var(char *var, char **ev);
char	*next_word(char *line);
int		insert_var(char **line, char *var, size_t n, char **ev);
int		variable_expansion(char **line, char **ev);

/* SIGNAL MANAGER */
void	int_signal(int n);
void	signal_manager(void);

/* BUILT-IN */
int		echo(t_cmdtab *cmdtab, char **args);
int		pwd(t_cmdtab *cmdtab, char **args);
int		ft_exit(t_cmdtab *cmdtab, char **args);
int		unset(t_cmdtab *cmdtab, char **args);
int		env(t_cmdtab *cmdtab, char **args);
int		export(t_cmdtab *cmdtab, char **args);
int		cd(t_cmdtab *cmdtab, char **args);

/* ENV */
bool	is_valid_env_var(char *var);
int		get_env_ind(t_cmdtab *cmdtab, char **env, char *var);
int		copy_env(t_cmdtab *cmdtab, char **ev);
int		set_env_var(t_cmdtab *cmdtab, char *var, char *val);
char	*get_env_val(t_cmdtab *cmdtab, char **env, char *var);

/* UTILS */
int		max(int a, int b);
int		split_len(char **split);
void	free_split(char ***split);
void	free_pointer(char **p);
void	free_cmdtab(t_cmdtab *cmdtab); //provisional, probablemente habrá que cambiarlo según se añadan más cosas
void	free_cmd(t_cmd *cmd);
int		error_msg(char *process, char *details, char *strerror, int error_code);

#endif /* MINISHELL_H */