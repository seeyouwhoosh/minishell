/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:55:19 by xwu               #+#    #+#             */
/*   Updated: 2026/01/21 13:10:00 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	char_in_charset(char c, const char *charset)
{
	size_t	j;

	j = -1;
	while (charset[++j])
	{
		if (c == charset[j])
			return (1);
	}
	return (0);
}

size_t	ft_strwords_charset(const char *s, const char *charset)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (char_in_charset(s[i], charset))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !char_in_charset(s[i], charset))
				i++;
		}
	}
	return (count);
}

char	**ft_split_charset(char const *s, const char *charset)
{
	size_t	i;
	size_t	j;
	size_t	ls;
	char	**result;

	result = malloc((ft_strwords_charset(s, charset) + 1) * sizeof(char *));
	if (!result || !s)
		return (free(result), NULL);
	i = 0;
	ls = 0;
	while (s[i])
	{
		if (!char_in_charset(s[i], charset))
		{
			j = i;
			while (s[i] && !ft_isspace(s[i]))
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