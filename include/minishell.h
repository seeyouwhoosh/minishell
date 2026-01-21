/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:46:16 by xwu               #+#    #+#             */
/*   Updated: 2026/01/21 13:00:41 by xwu              ###   ########.fr       */
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

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef TOKEN_DELIMITER
#  define TOKEN_DELIMITER " \t\r\n\a"
# endif

typedef struct s_cmds
{
	char	**split_cmd;
	int		infile;
	int		outfile;
	int		errfile;
	short	here_doc;
}			t_cmd;

typedef struct s_cmdtab
{
	t_cmd	*cmds;
	char	*cwd;
	char	*previous_wd;
	char	**env;
}			t_cmdtab;

enum 
{
	NO_REDIR,
	INFILE,
	OUTFILE,
	HERE_DOC,
	APPEND
};

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

#endif /* MINISHELL_H */