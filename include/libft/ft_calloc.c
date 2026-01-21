/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:05 by xwu               #+#    #+#             */
/*   Updated: 2025/04/19 18:41:48 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (!size || !nmemb)
	{
		return (malloc(1));
	}
	if (nmemb > SIZE_MAX / size)
	{
		return (NULL);
	}
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (!ptr)
	{
		return (NULL);
	}
	while (total_size)
	{
		total_size--;
		((char *)ptr)[total_size] = 0;
	}
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	char	*dest;
	char	*cptr;
	size_t	i;

	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	cptr = (char *)ptr;
	dest = malloc(size);
	if (!dest)
		return (NULL);
	if (!ptr)
		return (dest);
	i = -1;
	while (++i < old_size && i < size)
		dest[i] = cptr[i];
	free(ptr);
	return (dest);
}
