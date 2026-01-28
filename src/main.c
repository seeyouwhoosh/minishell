/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/01/28 20:34:28 by gcassi-d         ###   ########.fr       */
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

void	create_split(char ***split, char *s)
{
	*split = malloc(2 * sizeof(char *));
	if (!(*split))
		return ;
	(*split)[0] = ft_strdup(s);
	(*split)[1] = NULL;
}

void	append(char ***split, char *s)
{
	char	**old_split;
	char	**new_split;
	size_t	i;

	if (!split || !s)
		return ;
	old_split = *split;
	if (!old_split)
		return (create_split(split, s));
	i = 0;
	while (old_split[i])
		i++;
	new_split = malloc((i + 2) * sizeof(char *));
	if (!new_split)
	return ;
	i = -1;
	while (old_split[++i])
		new_split[i] = ft_strdup(old_split[i]);
	new_split[i] = ft_strdup(s);
	new_split[i + 1] = NULL;
	ft_freesplit(old_split);
	*split = new_split;
}

void	split_append(char *s, char ***split)
{
	char	**tmp;
	size_t	i;

	tmp = ft_split_charset(s, TOKEN_DELIMITER);
	i = 0;
	while (tmp[i])
		append(split, tmp[i++]);
	ft_freesplit(tmp);
}

/* Returns according to enum */
int		isredirecction(char *s)
{
	if (!ft_strcmp(s, "<"))
		return (INFILE);
	else if (!ft_strcmp(s, ">"))
		return (OUTFILE);
	else if (!ft_strcmp(s, ">>"))
		return (APPEND);
	else if (!ft_strcmp(s, "<<"))
		return (HERE_DOC);
	else
		return(NO_REDIR);
}

void	redirect(t_cmd *cmd, char *s)
{
	(void)cmd;
	(void)s;
	int	type;

	type = isredirecction(s);
	if (type == NO_REDIR)
		return ;
}

// Just discovered the case
/*
echo "hola"mevoy --> holamevoy
*/
int	str_to_cmd(char *s, t_cmd *cmd, char **ev)
{
	size_t	i;
	char *word;

	if (all_whitespace(s) || !ft_strcmp(s, ""))
		return (1);
	variable_expansion(&s, ev);
	i = -1;
	while (s[++i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && (matched_quote(s + i) != s + i))
		{
			append(&(cmd->split_cmd), ft_substr(s, i + 1, matched_quote(s + i) - s + i - 1));
			i += matched_quote(s + i) - s - i + 1;
		}
		else if (isredirecction(s + i))
			redirect(cmd, s + i);
		else
		{
			word = next_word(s + i);
			append(&(cmd->split_cmd), word);
			i += ft_strlen(word);
		}
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

int main(int ac, char **av, char **ev)
{
	(void)ac;
	char	*line = malloc(ft_strlen(av[1]) + 1);
	ft_memcpy(line, av[1], ft_strlen(av[1]));
	line[ft_strlen(av[1])] = 0;


	/* size_t	i = -1;
	cmdtab.env = ev;
	process_line(line, &cmdtab);
	while ((cmdtab.cmds)[++i].split_cmd)
		ft_putstrstr((cmdtab.cmds)[i++].split_cmd, '\n'); */

	printf("\n--- str_to_cmd() ---\n");
	t_cmd	cmd;
	cmd.split_cmd = NULL;
	str_to_cmd(line, &cmd, ev);
	ft_putstrstr(cmd.split_cmd, '\n');

	printf("\n--- append() ---\n");
	char **split;
	split = NULL;
	split_append("hola don pepito", &split);
	ft_putstrstr(split, '\n');
	append(&split, line);
	printf("\n--- (Changed) ---\n");
	ft_putstrstr(split, '\n');
}

/* int	main(int ac, char **av, char **ev)
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
} */
