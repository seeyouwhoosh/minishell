/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:46:16 by xwu               #+#    #+#             */
/*   Updated: 2026/01/18 13:13:08 by xwu              ###   ########.fr       */
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
# include "libft/libft.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef TOKEN_DELIMITER
# define TOKEN_DELIMITER " \t\r\n\a"
# endif

typedef struct s_cmds
{
	char	*cmd;
	char	**split_cmd;
	int		infile;
	int		outfile;
	int		errfile;
}			t_cmds;


typedef struct s_cmdtab
{
	t_cmds	*cmds;
	char	*cwd;
	char	*previous_wd;
	char	**env;
}			t_cmdtab;

/* void	(*built_in)(t_cmdtab *, char**) = {
	&echo,
	&pwd,
	&unset,
	&env,
	&export,
	&cd,
}; */

int	echo(t_cmdtab *cmdtab, char **args);
int	pwd(t_cmdtab *cmdtab, char **args);
//int	exit(t_cmdtab *cmdtab, char **args);
int	unset(t_cmdtab *cmdtab, char **args);
int	env(t_cmdtab *cmdtab, char **args);
int	export(t_cmdtab *cmdtab, char **args);
int	cd(t_cmdtab *cmdtab, char **args);

#endif /* MINISHELL_H */