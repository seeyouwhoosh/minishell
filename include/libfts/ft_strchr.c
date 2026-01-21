/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:14:12 by xiyu              #+#    #+#             */
/*   Updated: 2025/04/19 19:02:43 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*temp_s;

	temp_s = s;
	while (*temp_s)
	{
		if (*temp_s == (char)c)
		{
			return ((char *)temp_s);
		}
		temp_s++;
	}
	if ((char)c == '\0')
	{
		return ((char *)temp_s);
	}
	return (NULL);
}
