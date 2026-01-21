/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:20:39 by xiyu              #+#    #+#             */
/*   Updated: 2025/04/18 18:59:13 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	size_t	index;

	if (dest < src)
	{
		index = 0;
		while (count > index)
		{
			((char *)dest)[index] = ((const char *)src)[index];
			index++;
		}
	}
	else if (dest > src)
	{
		while (count)
		{
			((char *)dest)[count - 1] = ((const char *)src)[count - 1];
			count--;
		}
	}
	return (dest);
}
