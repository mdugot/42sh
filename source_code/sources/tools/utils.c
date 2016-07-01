/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 15:08:15 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/25 17:20:05 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>
#include <stdlib.h>

int		quit(t_shell *shell, int n)
{
	clean_exit(shell->edit->term, n, shell);
	return (n);
}

int		commun_char(char *s1, char *s2)
{
	while (*s1)
	{
		if (ft_strchr(s2, *s1))
			return (1);
		s1++;
	}
	return (0);
}

int		has_syntax_in(char *str)
{
	while (*str)
	{
		if (ft_strchr(SYNTAX, *str))
			return (1);
		str++;
	}
	return (0);
}
