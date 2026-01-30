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

/* Returns according to enum */
int	isredirecction(char *s)
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
		return (NO_REDIR);
}

void	redirect(t_cmd *cmd, char *s)
{
	int	type;

	(void)cmd;
	(void)s;
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
	char	*word;

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
