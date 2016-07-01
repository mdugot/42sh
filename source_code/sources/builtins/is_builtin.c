/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:09:13 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/27 19:57:27 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

int			is_builtin(const char *str)
{
	if (ft_strcmp(str, "cd") == 0
			|| ft_strcmp(str, "set") == 0
			|| ft_strcmp(str, "unset") == 0
			|| ft_strcmp(str, "setenv") == 0
			|| ft_strcmp(str, "unsetenv") == 0
			|| ft_strcmp(str, "env") == 0
			|| ft_strcmp(str, "exit") == 0
			|| ft_strcmp(str, "echo") == 0
			|| ft_strcmp(str, "history") == 0
			|| ft_strcmp(str, "read") == 0
			|| ft_strcmp(str, "export") == 0)
		return (1);
	return (0);
}
