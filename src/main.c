/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/01/18 13:18:09 by xwu              ###   ########.fr       */
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

int	process_line(char *line, t_cmdtab *cmdtab)
{
	char	**tokens;

	tokens = ft_split_charset(line, TOKEN_DELIMITER);
	if (!tokens)
		return (1);
	cmdtab->cmds
}

int	execute_line(t_cmdtab *cmdtab)
{
	
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
