/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/07 15:11:41 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(t_cmdtab *cmdtab)
{
	size_t	i;

	i = -1;
	while (cmdtab->n_cmds < ++i && cmdtab->cmds + i)
		free_cmd(cmdtab->cmds + i);
	free(cmdtab->cmds);
	cmdtab->cmds = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->split_cmd)
		free_split(&(cmd->split_cmd));
	if (cmd->here_doc)
		free_pointer(&(cmd->here_doc));
}

void	free_pointer(char **p)
{
	if (*p)
		free(*p);
	*p = NULL;
}

void	free_split(char ***split)
{
	size_t	i;

	i = -1;
	while ((*split)[++i])
		free_pointer(&((*split)[i]));
	free(*split);
	*split = NULL;
}

void	free_cmdtab(t_cmdtab *cmdtab)
{
	if (!cmdtab)
		return ;
	free_split(&(cmdtab->env));
	free_pointer(&(cmdtab->previous_wd));
	free_pointer(&(cmdtab->cwd));
	free_cmds(cmdtab);
	free(cmdtab);
}
/*
==598685== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
Minishell> 
==598669== Invalid free() / delete / delete[] / realloc()
==598669==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==598669==    by 0x109BB7: free_cmdtab (frees.c:58)
==598669==    by 0x109625: main (main.c:60)
==598669==  Address 0x1ffeffe9c0 is on thread 1's stack
==598669==  4016 bytes below stack pointer
==598669== 
==598669== 
==598669== HEAP SUMMARY:
==598669==     in use at exit: 212,445 bytes in 301 blocks
==598669==   total heap usage: 518 allocs, 218 frees, 241,460 bytes allocated
==598669== 
==598669== 34 (24 direct, 10 indirect) bytes in 1 blocks are definitely lost in loss record 17 of 69
==598669==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==598669==    by 0x10BEC5: ft_split_charset (in /home/xwu/Documents/minishell/minishell)
==598669==    by 0x1095D8: main (main.c:50)
==598669== 
==598669== 4,199 bytes in 73 blocks are definitely lost in loss record 55 of 69
==598669==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==598669==    by 0x10C08A: ft_strdup (in /home/xwu/Documents/minishell/minishell)
==598669==    by 0x109F94: copy_env (env_utils.c:27)
==598669==    by 0x109907: init_cmdtab (init.c:33)
==598669==    by 0x109500: main (main.c:27)
==598669== 
*/