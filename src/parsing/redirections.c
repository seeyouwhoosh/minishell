/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 15:25:21 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/12 23:20:22 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_hd(t_why a, size_t *i, short *squote, short *dquote)
{
	t_str	str;

	(*i)++;
	str = new();
	if (!str.str)
		return (error_msg("mnsh", NULL,
				"memory allocation failed", 1));
	while (is_whitespace(a.cmd->raw[*i]))
		(*i)++;
	if (!a.cmd->raw[*i] || a.cmd->raw[*i] == '<' || a.cmd->raw[*i] == '>')
		return (error_msg("mnsh", NULL,
				"error near unexpected token: `<<'", 2));
	while (!is_delimiter(a.cmd->raw[*i], *squote, *dquote))
	{
		if (quote_stuff(a.cmd->raw, i, squote, dquote))
			continue ;
		if (extend(&str))
			return (1);
		str.str[str.len] = a.cmd->raw[*i];
		str.len++;
		(*i)++;
	}
	return (opening(a, HERE_DOC, str));
}

static int	parse_ap(t_why a, size_t *i, short *squote, short *dquote)
{
	t_str	str;

	str = new();
	if (!str.str)
		return (error_msg("mnsh", NULL, "memory allocation failed", 1));
	(*i)++;
	while (is_whitespace(a.cmd->raw[*i]))
		(*i)++;
	if (!a.cmd->raw[*i] || a.cmd->raw[*i] == '<' || a.cmd->raw[*i] == '>')
		return (error_msg("mnsh", NULL,
				"error near unexpected token: `>>'", 2));
	while (!is_delimiter(a.cmd->raw[*i], *squote, *dquote))
	{
		if (quote_stuff(a.cmd->raw, i, squote, dquote))
			continue ;
		if (!*squote && a.cmd->raw[*i] == '$')
		{
			if (add_var(a, &str, i, squote))
				return (1);
			continue ;
		}
		if (add_to_str(a.cmd, i, &str))
			return (1);
	}
	return (opening(a, APPEND, str));
}

static int	parse_of(t_why a, size_t *i, short *squote, short *dquote)
{
	t_str	str;

	str = new();
	if (!str.str)
		return (error_msg("mnsh", NULL,
				"memory allocation failed", 1));
	while (is_whitespace(a.cmd->raw[*i]))
		(*i)++;
	if (!a.cmd->raw[*i] || a.cmd->raw[*i] == '<' || a.cmd->raw[*i] == '>')
		return (error_msg("mnsh", NULL,
				"error near unexpected token: `>'", 2));
	while (!is_delimiter(a.cmd->raw[*i], *squote, *dquote))
	{
		if (quote_stuff(a.cmd->raw, i, squote, dquote))
			continue ;
		if (!*squote && a.cmd->raw[*i] == '$')
		{
			if (add_var(a, &str, i, squote))
				return (1);
			continue ;
		}
		if (add_to_str(a.cmd, i, &str))
			return (1);
	}
	return (opening(a, OUTFILE, str));
}

static int	parse_if(t_why a, size_t *i, short *squote, short *dquote)
{
	t_str	str;

	str = new();
	if (!str.str)
		return (error_msg("mnsh", NULL,
				"memory allocation failed", 1));
	while (is_whitespace(a.cmd->raw[*i]))
		(*i)++;
	if (!a.cmd->raw[*i] || a.cmd->raw[*i] == '<' || a.cmd->raw[*i] == '>')
		return (error_msg("mnsh", NULL,
				"error near unexpected token: `<'", 2));
	while (!is_delimiter(a.cmd->raw[*i], *squote, *dquote))
	{
		if (quote_stuff(a.cmd->raw, i, squote, dquote))
			continue ;
		if (!*squote && a.cmd->raw[*i] == '$')
		{
			if (add_var(a, &str, i, squote))
				return (1);
			continue ;
		}
		if (add_to_str(a.cmd, i, &str))
			return (1);
	}
	return (opening(a, INFILE, str));
}

int	redirection(t_why a, size_t *i, short *squote, short *dquote)
{
	(*i)++;
	if (a.cmd->raw[*i - 1] == '<')
	{
		if (!a.cmd->raw[*i])
			return (error_msg("mnsh", NULL,
					"error near unexpected token: `<'", 2));
		if (a.cmd->raw[*i] == '<')
			return (parse_hd(a, i, squote, dquote));
		return (parse_if(a, i, squote, dquote));
	}
	if (!a.cmd->raw[*i])
		return (error_msg("mnsh", NULL,
				"error near unexpected token: `>'", 2));
	if (a.cmd->raw[*i] == '>')
		return (parse_ap(a, i, squote, dquote));
	return (parse_of(a, i, squote, dquote));
}
