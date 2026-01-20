/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/01/20 17:51:19 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
0. Separar por ; y hacer subprocesos según la cantidad de instrucciones (optativo, mejor que no)
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
		else if (!dquote  && line[i] == '|')
			count++;
	}
	return (count + 1);
}

char	*search_var(char *var, char **ev)
{
	size_t	i;
	char	*new_var;

	new_var = ft_strjoin(var, "=");
	i = -1;
	while (ev[++i])
	{
		if (!ft_strncmp(ev[i], new_var, ft_strlen(new_var)))
		{
			free(new_var);
			return (ev[i] + i + 1);
		}
	}
	free(new_var);
	return ("");
}

char	*next_word(char *line)
{
	char	*word;
	size_t	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, line, i);
	word[i] = 0;
	return (word);
}

int	insert_var(char **line, char *var, size_t n, char **ev)
{
	char	*new;
	size_t	ll;
	size_t	lv;
	char	*tmp;
	char	*expanded;

	expanded = search_var(var, ev);
	printf("%s", expanded);
	tmp = *line;
	ll = ft_strlen(*line);
	lv = ft_strlen(expanded);
	new = malloc(ll + lv + 1);
	if (!new)
		return (0);
	ft_memcpy(new, *line, n);
	ft_memcpy(new + n, expanded, lv);
	ft_memcpy(new + n + lv, *line + n, ll - n);
	new[ll + lv] = 0;
	free(tmp);
	*line = new;
	return (lv);
}

int	variable_expansion(char **line, char **ev)
{
	short	dquote;
	size_t	i;
	char	*var;

	i = 0;
	dquote = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'')
			dquote = (dquote + 1) % 2;
		else if ((*line)[i] == '$')
		{
			var = next_word(*line + i + 1);
			if (!var)
				return (1);
			i += insert_var(line, var, i, ev);
			free(var);
			break;
		}
		i++;
	}
	return (0);
}

/* int	process_line(char *line, t_cmdtab *cmdtab)
{
	char	**tokens;
	int		i;
	size_t	number_cmds;
	short	quote;

	cmdtab->cmds = malloc(n_cmds(line) * sizeof(t_cmds));
	variable_expansion(&line, cmdtab->env);
	tokens = ft_split_charset(line, TOKEN_DELIMITER);
	if (!tokens)
		return (1);
	i = 0;
	quote = 0;
	while (*tokens)
	{
		if (line[i] == '\"')
			quote = (quote + 1) % 2;
		else if (ft_strcmp(tokens[i], "|"))
			i++;
		tokens++;
	}
} */

/* int	execute_line(t_cmdtab *cmdtab)
{
	;
} */

int main(int ac, char **av, char **ev)
{
	(void)av;
	(void)ac;
	char	*line = malloc(6);
	ft_memcpy(line, "$INFOPATH", 5);
	line[5] = 0;
	variable_expansion(&line, ev);
    printf("%s", line);
}

/* int	main(int ac, char **av, char **ev)
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
} */
