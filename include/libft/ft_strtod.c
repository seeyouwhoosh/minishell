/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:34:54 by xwu               #+#    #+#             */
/*   Updated: 2025/08/22 12:34:54 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

int	ft_power(int base, int exp)
{
	int	n;

	n = 1;
	if (base == 0 || exp < 0)
		return (0);
	while (exp > 0)
	{
		if (exp % 2 == 1)
			n *= base;
		base *= base;
		exp /= 2;
	}
	return (n);
}

size_t	decimal_part(const char *restrict str, double *number)
{
	size_t			index;
	unsigned int	digits;
	int				sign;

	sign = 1;
	index = 0;
	if (str[index] == '-' || str[index] == '+')
		if (str[index++] == '-')
			sign = -1;
	*number = (double)ft_atoi(&(str[index]));
	while (ft_isdigit(str[index]))
		index++;
	if (str[index] == '.')
	{
		index++;
		digits = index;
		while (ft_isdigit(str[digits]))
			digits++;
		if (digits > index)
			*number += (double)ft_atoi(&(str[index]))
				/ (double)ft_power(10, digits - index);
		index = digits;
	}
	*number *= sign;
	return (index);
}

double	ft_strtod(const char *restrict str, char **restrict endptr)
{
	size_t	index;
	double	number;
	int		power;

	number = 0.0;
	index = decimal_part(str, &number);
	if (str[index] == 'e' || str[index] == 'E')
	{
		index++;
		power = ft_atoi(&(str[index]));
		if (power > 0)
			number *= ft_power(10, power);
		else if (power < 0)
			number /= ft_power(10, -power);
		while (ft_isdigit(str[index]) || str[index] == '+' || str[index] == '-')
			index++;
	}
	if (endptr)
		*endptr = (char *)&str[index];
	return (number);
}
