/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:55:19 by xwu               #+#    #+#             */
/*   Updated: 2025/11/09 22:21:12 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	index;
	size_t	n;

	n = ft_strlen(s1);
	if (ft_strlen(s2) > n)
		n = ft_strlen(s2);
	index = 0;
	while (n > index)
	{
		if (s1[index] != s2[index])
		{
			return (s1[index] - s2[index]);
		}
		index++;
	}
	return (0);
}

int	charset_in_str(const char *str, const char *charset)
{
	size_t	i;
	size_t	j;

	if (!str || !charset || !(*charset) || !(*str))
		return (0);
	i = -1;
	while (charset[++i])
	{
		j = -1;
		while (str[++j])
		{
			if (charset[i] == str[j])
				return (1);
		}
	}
	return (0);
}

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

size_t	ft_strwords(const char *s, const char *charset)
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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
	{
		return ((char *)big);
	}
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j])
		{
			if (little[j + 1] == '\0')
			{
				return (&((char *)big)[i]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
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

char	**ft_split(char const *s, const char *charset)
{
	size_t	i;
	size_t	j;
	size_t	ls;
	char	**result;

	result = malloc((ft_strwords(s, charset) + 1) * sizeof(char *));
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

void	ft_putstrstr(char **s, char sep)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write(1, s[i], ft_strlen(s[i]));
		if (s[i + 1])
			write(1, &sep, 1);
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