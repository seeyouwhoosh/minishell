/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:13:09 by xiyu              #+#    #+#             */
/*   Updated: 2025/04/18 18:58:54 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			index;
	unsigned char	*b_copy;

	index = 0;
	b_copy = (unsigned char *)b;
	while (n > index)
	{
		b_copy[index] = (unsigned char)c;
		index++;
	}
	return (b);
}
