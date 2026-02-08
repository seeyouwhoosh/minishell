/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:46:16 by xwu               #+#    #+#             */
/*   Updated: 2026/02/08 22:54:34 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line.h"
# include "libft.h"
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
	char	*raw;
	int		infile;
	int		outfile;
	int		last;
	char	*here_doc;
}			t_cmd;

typedef struct s_cmdtab
{
	t_cmd	*cmds;
	int		stdout_fd;
	int		stdin_fd;
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
	R_HERE_DOC,
	R_APPEND,
	R_OUTFILE,
	R_INFILE,
	FILE_NOT_FOUND,
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
int		error_msg(char *process, char *details, char *strerror, int error_code);
bool	is_whitespace(int c);
int		all_whitespace(char	*s);
int		ft_dup(int new_fd, int og_fd);
char	*get_path(char *cmd, char **env);

/* PARSING */
int		cmds_am(char *line, size_t *holder);
int		get_commands(t_cmd *cmd, char *str, size_t max);
char	*get_next_command(t_cmd *cmd, char *pos, size_t ind, t_str str);
int		extend(t_str *str);
int		is_delimiter(int c, short squote, short dquote);
t_str	new(void);
int		add_var(t_why a, t_str *str, size_t *i, short *squote);
int		get_token(t_why a, size_t *i, short *squote, short *dquote);
int		parse_command(t_cmdtab *cmdtab, t_cmd *cmd);
int		redirection(t_why a, size_t *i, short *squote, short *dquote);
bool	quote_stuff(char *str, size_t *i, short *squote, short *dquote);
int		opening(t_why a, int mode, t_str str);
int		ft_open(const char *filename, int mode);
int		parse_main(t_cmdtab *cmdtab, char *cmd);
int		append(char *s, char ***split);
int		add_to_str(t_cmd *cmd, size_t *i, t_str *str);
int		check_rest(t_cmd *cmd, size_t i, size_t max);

/* EXECUTING */
int		execute_all(t_cmdtab *cmdtab);
int		exec_cmd(t_cmd *cmd, t_cmdtab *cmdtab);
int		manage_infile(t_cmd *cmd, t_cmdtab *cmdtab, int fd[2]);
int		manage_outfile(t_cmd *cmd, t_cmdtab *cmdtab, int fd[2]);
int		manage_last_outfile(t_cmd *cmd, t_cmdtab *cmdtab);
int		just_redirection(t_cmd *cmd);
void	exec_pipe_cmd(t_cmdtab *cmdtab, t_cmd *cmd, int fd[2]);
int		exec_last_cmd(t_cmd *cmd, t_cmdtab *cmdtab);
int		exec_bin(char **split_cmd, t_cmdtab *cmdtab);
int		exec_last_builtin(t_cmd *cmd, t_cmdtab *cmdtab);
int		which_exit(int status);
int		is_builtin(char *str_cmd, t_cmdtab *cmdtab);
int		builtin_cmd(t_cmd *cmd, t_cmdtab *cmdtab, int code);
int		exec_builtin(t_cmd *cmd, t_cmdtab *cmdtab, int fd[2]);

/* HERE_DOC */
int		here_doc(char *limiter, size_t n_cmds);
void	here_doc_put(char *limiter, size_t n_cmds, int fd);
void	put_heredoc_prompt(size_t n_cmds);
char	*get_next_line(int fd);
void	get_line(int fd, char **line, size_t size);

#endif /* MINISHELL_H */