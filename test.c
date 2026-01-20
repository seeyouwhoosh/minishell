/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:48:23 by xwu               #+#    #+#             */
/*   Updated: 2026/01/20 01:56:08 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	total_size;

	if (!s1 || !s2)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(total_size);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t		index;
	char		*dst_copy;
	const char	*src_copy;

	if (!dst && !src && n > 0)
		return (NULL);
	dst_copy = (char *)dst;
	src_copy = (const char *)src;
	index = 0;
	while (n > index)
	{
		dst_copy[index] = src_copy[index];
		index++;
	}
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		i++;
	}
	if (size == 0)
	{
		return (i);
	}
	while (size - 1 && *src)
	{
		*dst = *src;
		dst++;
		src++;
		size--;
	}
	*dst = '\0';
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = strlen(dst);
	src_len = strlen(src);
	i = 0;
	if (size <= dst_len)
	{
		return (src_len + size);
	}
	while (dst_len + i < size - 1 && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

char	*search_var(char *var, char **ev)
{
	size_t	i;
	char	*new_var;

	new_var = ft_strjoin(var, "=");
	i = -1;
	while (ev[++i])
	{
		if (!strncmp(ev[i], new_var, strlen(new_var)))
		{
			free(new_var);
			return (ev[i] + i + 1);
		};
	}
	free(new_var);
	return ("");
}

char	*next_word(char *line)
{
	char	*tmp;
	char	*word;
	size_t	i;

	i = 0;
	while (line[i + 1] && line[i + 1] != ' ')
		i++;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, line, i + 2);
	word[i + 2] = 0;
	return (word);
}

int	insert_var(char **line, char *var, size_t n)
{
	char	*new;
	size_t	ll;
	size_t	lv;
	char	*tmp;

	tmp = *line;
	ll = strlen(*line);
	lv = strlen(var);
	new = malloc(ll + lv + 1);
	if (!new)
		return (1);
	ft_memcpy(new, *line, n);
	ft_memcpy(new + n, var, lv);
	ft_memcpy(new + n + lv, *line + n, ll - n);
	new[ll + lv] = 0;
	free(tmp);
	*line = new;
	return (0);
}

int	variable_expansion(char **line, char **ev)
{
	short	dquote;
	size_t	i;
	char	*var;

	i = -1;
	dquote = 0;
	while ((*line)[++i])
	{
		if ((*line)[i] == '$')
		{
			var = next_word(&(*line)[i]);
			if (!var)
				return (1);
			if (*search_var(var, ev))
				if (insert_var(line, var, i))
					return (1);
			i += strlen(var);
			free(var);
		}
	}
	return (0);
}

int main(int ac, char **av, char **ev)
{
	char	*line = malloc(6);
	ft_memcpy(line, "$PATH", 5);
	line[5] = 0;
	variable_expansion(&line, ev);
    printf("%s", line);
}