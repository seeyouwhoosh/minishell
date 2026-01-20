/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:59:07 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/01/20 23:47:56 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

Hola, Koitz :D
Te dejo aquí los snippets de los apuntes (que seguro que no has mirado) de las
funciones que podemos usar. No sé si para el cd podría haber algún problema con
los permisos, así que te he dejado las funciones relevantes.

*/

/* @ Mira si los permisos de un archivo son correctos
@ int mode: Bitwise-inclusive OR of the access permissions to be checked (R_OK, W_OK, X_OK)
or the existence test (F_OK)
@ return: 0 si no hay ningún problema, -1 otherwise, que hay específicos, según definidos */
int access(const char *pathname, int mode);

/* @ Es como un "cd", funciona para ".." */
int chdir(const char *path);

/* Get file information */
int stat(const char *restrict path, struct stat *restrict statbuf);
int fstat(int fd, struct stat *statbuf);
int lstat(const char *restrict path, struct stat *restrict statbuf);

int		cd(t_cmdtab *cmdtab, char **args)
{
	return (0);
}
