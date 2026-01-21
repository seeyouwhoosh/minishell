/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:18:49 by xwu               #+#    #+#             */
/*   Updated: 2025/04/25 18:44:38 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int n)
{
	long	nbr_cpy;
	size_t	i;

	i = 0;
	nbr_cpy = n;
	if (nbr_cpy <= 0)
	{
		i++;
		nbr_cpy = -nbr_cpy;
	}
	while (nbr_cpy > 0)
	{
		nbr_cpy /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*nbr_str;
	long	nbr_cpy;
	size_t	i;

	i = ft_intlen(n);
	nbr_cpy = n;
	nbr_str = malloc(i + 1);
	if (!nbr_str)
		return (NULL);
	if (nbr_cpy == 0)
		nbr_str[0] = '0';
	else if (nbr_cpy < 0)
	{
		nbr_cpy = -nbr_cpy;
		nbr_str[0] = '-';
	}
	nbr_str[i] = '\0';
	while (nbr_cpy > 0)
	{
		i--;
		nbr_str[i] = (nbr_cpy % 10) + '0';
		nbr_cpy /= 10;
	}
	return (nbr_str);
}
/*
#include <stdio.h>
int main() {
	int numero = ;
	char *str;
	str = ft_itoa(numero);  // base 10 = decimal

	printf("Número original: %d\n", numero);
	printf("Convertido con itoa: %s\n", str);

	return 0;
}
*/