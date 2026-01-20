/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/01/20 23:28:37 by xwu              ###   ########.fr       */
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

char	**tokenize(char *line, char **ev)
{
	size_t	i;

	i = -1;
	while (line[++i])
	{
		if (isredirecction(line[i]))
			; //coger el elemento justamente posterior ó coger el siguiente token
		if (!matched_quote(line))
			; //almacenar el coso entero como token
		else
			;
	}
}

void	str_to_cmd(char *s, t_cmd cmd, char **ev)
{
	
	free(s);
}

int	process_line(char *line, t_cmdtab *cmdtab)
{
	size_t	ncmds;
	short	quote;
	size_t	j;
	size_t	k;

	ncmds = n_cmds(line);
	cmdtab->cmds = malloc(ncmds * sizeof(t_cmd) + 1);
	if (!cmdtab->cmds)
		return (1);
	cmdtab->cmds[ncmds].cmd = NULL;
	j = -1;
	k = 0;
	while (line[++j])
	{
		if ((line[j] == '\'' || line[j] == '\"'))
			quote = matched_quote(line);
		if ((line[j] == '|' && (line + j) > quote) || ((j + 1) == ft_strlen(line)))
		{
			str_to_cmd(ft_substr(line, k, j + 1), *(cmdtab->cmds)++, cmdtab->env);
			k = j + 1;
		}
	}
}
void	free_cmds(t_cmd *cmds)
{
	size_t	i;

	i = -1;
	while (cmds[++i].cmd) //por si se alloca algo allí
	{
		;
	}
	free(cmds);
}


int	execute_line(t_cmdtab *cmdtab)
{
	
	free_cmds(cmdtab->cmds);
}

int	main(int ac, char **av, char **ev)
{
	char		*line;
	t_cmdtab	*cmdtab;

	(void)av;
	if (ac != 1)
		return(write(1, "\e[1;31mInvalid arguments\e[0m\n", 29));

	signal_manager();
	cmdtab->env = ev;
	line = (char *)1;
	while (line)
	{
		line = readline("Minishell> ");
		rl_on_new_line();
		if (all_whitespace(line))
			continue ;
		process_line(line, cmdtab);
		execute_line(cmdtab);
		add_history(line);
		free(line);
	}
}
