/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:05:48 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/06 00:42:06 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	quote_stuff(char *str, size_t *i, short *squote, short *dquote)
{
	if (!*squote && str[*i] == '\"')
	{
		*dquote = 1 - *dquote;
		return (true);
	}
	else if (!*squote && *i == '\'')
	{
		*squote = 1 - *squote;
		return (true);
	}
	return (false);
}

int	get_token(t_why a, size_t *i, short *squote, short *dquote)
{
	t_str	str;
	int		flag;

	if (a.cmd->raw[*i] == '>' || a.cmd->raw[*i] == '<')
		redirection(a.cmd, i, squote, dquote);
	str = new();
	while (!is_delimiter(a.cmd->raw[*i], *squote, *dquote))
	{
		if (quote_stuff(a.cmd->raw, i, squote, dquote))
			continue ;
		if (!squote && a.cmd->raw[*i] == '$')
		{
			flag = add_var(a, &str, i, squote);
			if (flag)
				return (flag);
			continue ;
		}
		if (extend(&str))
			return (MALLOC);
		str.str[str.len] = a.cmd->raw[*i];
		str.len++;
		(*i)++;
	}
	return (append(str, &(a.cmd->split_cmd)));
}

int	parse_command(t_cmdtab *cmdtab, t_cmd *cmd)
{
	short	squote;
	short	dquote;
	size_t	i;
	int		flag;
	t_why	a;

	a.cmd = cmd;
	a.cmdtab = cmdtab;

	squote = 0;
	dquote = 0;
	i = 0;
	while (is_whitespace(cmd->raw[i]))
		i++;
	while (cmd->raw[i])
	{
		flag = get_token(a, &i, &squote, &dquote);
		if (flag)
			return (flag);
		while (is_whitespace(cmd->raw[i]))
			i++;
	}
	return (SUCCESS);
}

static int	check_empty(t_cmdtab *cmdtab)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < cmdtab->n_cmds)
	{
		if ((!cmdtab->cmds[i].split_cmd || !cmdtab->cmds[i].split_cmd[0]) && i)
			return (PIPE);
	}
	return (SUCCESS);
}

//orden: pipes, tokens, locate redirections, env_vars
int	parse_main(t_cmdtab *cmdtab, char *cmd)
{
	size_t	i;
	int		flag;

	flag = cmds_am(cmd, &(cmdtab->n_cmds));
	if (flag)
		return (free(cmd), flag);
	cmdtab->cmds = ft_calloc(cmdtab->n_cmds + 1, sizeof(t_cmd));
	correct_outfile(cmdtab);
	if (!cmdtab->cmds)
		return (free(cmd), MALLOC);
	flag = create_raws(cmdtab->cmds, cmd);
	if (flag)
		return (free(cmd), flag);
	flag = get_commands(cmdtab->cmds, cmd);
	if (flag)
		return (free(cmd), flag);
	i = -1;
	while (++i < cmdtab->n_cmds)
	{
		flag = parse_command(cmdtab, cmdtab->cmds + i);
		if (flag)
			return (free(cmd), flag);
	}
	return (free(cmd), check_empty(cmdtab->cmds));
}
