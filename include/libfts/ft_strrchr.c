/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:15:22 by xiyu              #+#    #+#             */
/*   Updated: 2025/04/19 19:03:19 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*temp_s;
	const char	*ptr_c;

	temp_s = s;
	ptr_c = NULL;
	while (*temp_s)
	{
		if (*temp_s == (char)c)
		{
			ptr_c = temp_s;
		}
		temp_s++;
	}
	if ((char)c == '\0')
		return ((char *)temp_s);
	return ((char *) ptr_c);
}
