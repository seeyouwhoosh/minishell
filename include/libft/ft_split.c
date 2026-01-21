/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:55:19 by xwu               #+#    #+#             */
/*   Updated: 2025/04/25 20:18:15 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strwords(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

void	ft_freesplit(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

static char	*ft_wordcpy(const char *s, size_t j, size_t i)
{
	char	*word;

	word = malloc(i - j + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, &s[j], i - j + 1);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	ls;
	char	**result;

	result = malloc((ft_strwords(s, c) + 1) * sizeof(char *));
	if (!result || !s)
		return (free(result), NULL);
	i = 0;
	ls = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] && s[i] != c)
				i++;
			result[ls++] = ft_wordcpy(s, j, i);
			if (!result[ls - 1])
				return (ft_freesplit(result), NULL);
		}
		else
			i++;
	}
	return (result[ls] = NULL, result);
}

void	ft_putstrstr(char **s, char sep)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		ft_putstr_fd(s[i], 1);
		if (s[i + 1])
			ft_putchar_fd(sep, 1);
		i++;
	}
}

/* #include <stdio.h>
int main(void)
{
	char *str = "Hello World";
	
	char **strstr = ft_split(str, ' ');
	size_t	n = ft_strwords(str, ' ');
	ft_putstrstr(strstr, n);
	ft_freesplit(strstr);
	printf("Número de palabras en la frase \"%s\" es %zu", str, n);
	return (0);
}
 */