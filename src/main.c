/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/01/27 19:58:03 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
1. AÚN QUEDA POR PENSAR EN QUÉ ORDEN PARSEAR LAS EXPANSIONES Y LAS COMILLAS
2. Parsear comandos por pipes
3. Parsear redirecciones. Tener en cuenta que si tiene infile, se redirecciona tanto el infile como el pipe anterior; lo mismo con el outfile
	3.1. Redireccionar el stderr, casos especiales (mirar apuntes)

A partir de aquí, proceso parecido al pipex (más detallado por si acaso)

4. Crear un subproceso para cada línea
	4.1. Separar línea, mirar si el primer coso es built-in
		3.1.1. Sí: redirigir a la función en concreto
		3.1.2. No
	4.2. (3.1.2). Encontrar archivo binario en path.
	4.3. Matarse.
*/

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

size_t	n_cmds(char *line)
{
	size_t	i;
	short	squote;
	short	dquote;
	size_t	count;

	squote = 0;
	dquote = 0;
	count = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"')
			dquote = (dquote + 1) % 2;
		if (line[i] == '\'')
			squote = (squote + 1) % 2;
		else if ((!dquote || !squote) && line[i] == '|')
			count++;
	}
	return (count + 1);
}
/* Find match. Returns match; if not match, returns itself */
char	*matched_quote(char *line)
{
	size_t	i;

	i = 0;
	while (line[++i] && line[i] != line[0])
		;
	if (!line[i])
		return (line);
	return (line + i);
}

void	append(char ***split, char *start, char *end)
{
	char	**old_split;
	char	**new_split;
	size_t	i;

	old_split = *split;
	if (!split)
	{
		*split = malloc(2 * sizeof(char *));
		ft_strlcpy((*split)[0], start, end - start + 1);
		(*split)[1] = NULL;
		return ;
	}
	i = 0;
	while (!(*split)[i++])
		;
	new_split = malloc((i + 2) * sizeof(char *));
	i = -1;
	while (!(*split)[++i])
		new_split[i] = (*split)[i];
	ft_strlcpy(new_split[i], start, end - start + 1);
	*split = new_split;
	ft_freesplit(old_split);
}

void	split_append(char *s, char ***split)
{
	char	**tmp;
	tmp = ft_split_charset(s, TOKEN_DELIMITER) - 1;
	while (++tmp)
		append(split, *tmp, *tmp + ft_strlen(*tmp) - 1);
	ft_freesplit(tmp);
}

/* Returns according to enum */
int		isredirecction(char *s)
{
	if (ft_strcmp(s, "<"))
		return (INFILE);
	else if (ft_strcmp(s, ">"))
		return (OUTFILE);
	else if (ft_strcmp(s, ">>"))
		return (APPEND);
	else if (ft_strcmp(s, "<<"))
		return (HERE_DOC);
	else
		return(NO_REDIR);
}

void	redirect(t_cmd *cmd, char *s, int type)
{
	(void)cmd;
	(void)s;
	if (type == NO_REDIR)
		return ;
}

int	str_to_cmd(char *s, t_cmd *cmd, char **ev)
{
	size_t	i;

	if (all_whitespace(s) || !s[0])
		return (free(s), 1);
	variable_expansion(&s, ev);
	free(s);
	i = -1;
	while (s[++i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && (matched_quote(s + i) != s + i))
		{
			append(&(cmd->split_cmd), s + i + 1, matched_quote(s + i) - 1);
			i = matched_quote(s + i) - s + 1;
		}
		else if (isredirecction(s + i))
			redirect(cmd, s + i, isredirecction(s + i));
		else
			split_append(s, &(cmd->split_cmd));
	}
	return (0);
}

int	process_line(char *line, t_cmdtab *cmdtab)
{
	size_t	ncmds;
	char	*quote;
	size_t	j;
	size_t	k;

	ncmds = n_cmds(line);
	cmdtab->cmds = malloc(ncmds * sizeof(t_cmd) + 1);
	if (!cmdtab->cmds)
		return (1);
	cmdtab->cmds[ncmds].split_cmd = NULL;
	j = -1;
	k = 0;
	while (line[++j])
	{
		if ((line[j] == '\'' || line[j] == '\"'))
			quote = matched_quote(line);
		if ((line[j] == '|' && (line + j) > quote) || ((j + 1) == ft_strlen(line)))
		{
			if (str_to_cmd(ft_substr(line, k, j + 1), cmdtab->cmds++, cmdtab->env))
				return (1);
			k = j + 1;
		}
	}
	return (0);
}
void	free_cmds(t_cmdtab *cmdtab)
{
	size_t	i;

	i = -1;
	while (cmdtab->cmds[++i].split_cmd)
		ft_freesplit(cmdtab->cmds[++i].split_cmd);
	free(cmdtab->cmds);
}


int	execute_line(t_cmdtab *cmdtab)
{
	free_cmds(cmdtab);
	return (0);
}

int	main(int ac, char **av, char **ev)
{
	char		*line;
	t_cmdtab	*cmdtab;

	(void)av;
	if (ac != 1)
		return (write(1, "\e[1;31mInvalid arguments\e[0m\n", 29));
	signal_manager();
	cmdtab = malloc(sizeof(cmdtab));
	if (!cmdtab)
		return (1);
	if (copy_env(cmdtab, ev))
		return (free(cmdtab), 1);
	line = (char *)1;
	while (line)
	{
		line = readline("Minishell> ");
		rl_on_new_line();
		if (all_whitespace(line))
			continue ;
		if (!process_line(line, cmdtab))
			execute_line(cmdtab);
		add_history(line);
		free(line);
	}
}
