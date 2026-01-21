/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:34:03 by xwu               #+#    #+#             */
/*   Updated: 2025/04/25 18:51:06 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Aplica la función ’f’ a cada carácter de la cadena
’s’, pasando su índice como primer argumento y el
propio carácter como segundo argumento. Se crea una
nueva cadena (utilizando malloc(3)) para recoger
los resultados de las sucesivas aplicaciones de
’f’ */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*result;

	if (!s || !f)
		return (NULL);
	i = 0;
	result = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
#include <stdio.h>

char	upp(unsigned int _i, char c)
{
	if ('a' <= c && c <= 'z')
		return (c - 'a' + 'A');
	else
		return c;
}
int main(void) 
{
   
	char str[] = "hola mundo";
    
    char *result = ft_strmapi(str, upp);

    if (result) {
        printf("Original: %s\n", str);
        printf("Modificada: %s\n", result);
        free(result); 
    }
    return 0;
}
*/
