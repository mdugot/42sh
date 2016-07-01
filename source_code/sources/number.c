/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 11:51:52 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 11:51:54 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		len_number(const char *str)
{
	int n;

	n = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (n);
		n++;
		str++;
	}
	return (n);
}

int		is_positive_number(const char *str)
{
	int n;

	n = 0;
	while (*str)
	{
		n++;
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (n);
}

int		read_positive_number(char **str, int modulo)
{
	int	r;

	if (!ft_isdigit((*str)[0]))
		return (-1);
	r = ft_atoi(*str);
	while (ft_isdigit((*str)[0]))
		*str += 1;
	if (modulo)
		r %= modulo;
	return (r);
}
