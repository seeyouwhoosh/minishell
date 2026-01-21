/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:13:52 by xwu               #+#    #+#             */
/*   Updated: 2025/04/25 19:36:41 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	abs_len;

	abs_len = ft_strlen(s) + 1;
	ptr = malloc(abs_len);
	if (!ptr)
	{
		return (NULL);
	}
	ptr[abs_len - 1] = '\0';
	while (abs_len)
	{
		abs_len--;
		ptr[abs_len] = s[abs_len];
	}
	return (ptr);
}
