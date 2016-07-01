/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:01:00 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/10 18:22:41 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	int result;
	int sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (*str - '0') + result * 10;
		str++;
	}
	return (result * sign);
}

unsigned int	ft_atoi_base(const char *str, int base)
{
	int		result;
	char	*ascii;

	if (base < 2)
		base = 2;
	if (base > 16)
		base = 16;
	ascii = "0123456789ABCDEF";
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	while (*str >= ascii[0] && *str <= ascii[base - 1])
	{
		result = (*str - '0') + result * base;
		str++;
	}
	return (result);
}

long long int	ft_atol(const char *str)
{
	long long int	result;
	int				sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (*str - '0') + result * 10;
		str++;
	}
	return (result * (long long int)sign);
}
