/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:46:16 by xwu               #+#    #+#             */
/*   Updated: 2026/02/06 00:13:35 by xwu              ###   ########.fr       */
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

/* typedef struct s_file
{
	char	*name;
	int		fd;
	int		mode;
}			t_file;
 */
typedef struct s_cmds
{
	char	**split_cmd;
	char	*raw; //para facilitar la vida
	int		infile; //cat < a <c
	int		outfile;
	int		last;
	char	*here_doc;
}			t_cmd;

typedef struct s_cmdtab
{
	t_cmd	*cmds;
	int		stdout_fd;
	size_t	n_cmds;
	char	*cwd;
	char	*previous_wd;
	char	**env;
	int		env_capacity;
	int		env_len;
	int		exit_code;
}			t_cmdtab;

typedef struct s_str
{
	char	*str;
	size_t	len;
	size_t	capacity;
}	t_str;

typedef struct s_why
{
	t_cmd		*cmd;
	t_cmdtab	*cmdtab;
}	t_why;

enum e_modes
{
	NO_REDIR,
	INFILE,
	OUTFILE,
	HERE_DOC,
	APPEND
};

enum e_builtins
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
};

enum
{
	SUCCESS,
	MALLOC,
	MISMATCHED_SQUOTE,
	MISMATCHED_DQUOTE,
	PIPE,

};

/* INITS */
int		init_cmdtab(t_cmdtab *cmdtab, char **ev);
void	correct_outfile(t_cmdtab *cmdtab);

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

/* FIND BUILT-IN*/
int		is_builtin(char *str_cmd, t_cmdtab *cmdtab);
int		exec_builtin(t_cmd *cmd, t_cmdtab *cmdtab);

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
int		error_msg(char *process, char *details, char *strerror, int error_code);
bool	is_whitespace(int c);
int		all_whitespace(char	*s);

/* PARSING */
int		cmds_am(char *line, size_t *holder);
int		get_commands(t_cmd *cmd, char *str);
char	*get_next_command(t_cmd *cmd, char *pos, size_t ind, t_str str);
int		extend(t_str *str);
int		is_delimiter(int c, short squote, short dquote);
t_str	new(void);
int		add_var()

#endif /* MINISHELL_H */