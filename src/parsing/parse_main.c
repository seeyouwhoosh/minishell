/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:05:48 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/01 20:46:04 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//not_done... I hate this
static size_t	n_token(char *cmd, size_t pos)
{
	size_t	count;
	char	c;

	count = 0;
	while (cmd[pos] && cmd[pos] != "|")
	{
		while (cmd[pos] && is_whitespace(cmd[pos]))
			pos++;
		if (cmd[pos] == '\"' || cmd[pos] == '\'' )
		{
			c = cmd[pos];
			while (cmd[pos] != c)
				pos++;
			count++;
		}
		else if (cmd[pos] == '<' || cmd[pos] == '>')
			count++;
		pos++;
	}
	return (count + 1);
}

int	add_tokens(t_cmd *cmd_ui, char **split_cmd, char *cmd, size_t pos)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (cmd[pos] && cmd[pos] != '|')
	{
		while (cmd[pos] && is_whitespace(cmd[pos]))
			pos++;
		if (cmd[pos] == '\'')
			flag = add_squote(cmd_ui, cmd, pos, i++);
		else if (cmd[pos] == '\"')
			flag = add_dquote(cmd_ui, cmd, pos, i++);
	}
	return (SUCCESS);
}

int	add_next_cmd(t_cmdtab *cmdtab, size_t ind, char *cmd)
{
	size_t	pos;
	int		flag;

	pos = nth_cmd(cmd, ind);
	cmdtab->cmds[ind].split_cmd = ft_calloc(sizeof(char *),
			n_token(cmd, pos) + 1);
	flag = add_tokens(cmdtab->cmds + ind,
			cmdtab->cmds[ind].split_cmd, cmd, pos);
	if (flag)
		return (flag);
}

//orden: pipes, tokens, locate redirections, env_vars
//ok so all redirections look at filename after vars are written in, except heardoc because why not, let's make things not consistant, yes, what a wonderful design yayyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
int	parse_main(t_cmdtab *cmdtab, char *cmd)
{
	size_t	cmd_am;
	size_t	i;
	int		flag;

	cmd_am = c_cmds(cmd);
	if (!cmd_am)
		return (MISMATCHED_QUOTES);
	cmdtab->cmds = ft_calloc(cmd_am + 1, sizeof(t_cmd));
	if (!cmdtab->cmds)
		return (MALLOC);
	i = -1;
	while (++i < cmd_am)
	{
		flag = add_next_cmd(cmdtab, i, cmd);
		if (flag)
			return (flag);
	}
	free(cmd);
	return (SUCCESS);
}
