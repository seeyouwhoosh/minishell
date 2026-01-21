/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:39:42 by xwu               #+#    #+#             */
/*   Updated: 2025/04/18 18:57:34 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_copy;

	s_copy = (const unsigned char *)s;
	while (n)
	{
		if (*s_copy == (unsigned char)c)
		{
			return ((void *)s_copy);
		}
		n--;
		s_copy++;
	}
	return (NULL);
}
