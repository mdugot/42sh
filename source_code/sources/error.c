/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:08:31 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/25 16:21:09 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

void	exit_error(char *str)
{
	if (str != NULL)
		ft_printf_fd(1, "ERROR : %s\n", str);
	else
		ft_printf_fd(1, "ERROR\n");
	exit(1);
}

void	*secure_alloc(size_t size)
{
	void *result;

	result = ft_memalloc(size);
	if (result == NULL)
		exit_error("Malloc has encountered a problem.");
	return (result);
}

void	exec_error(t_command *command, int fd)
{
	ft_printf_fd(fd, "42sh: ");
	if (command->error_message)
		ft_printf_fd(fd, "%s", command->error_message);
	else
		ft_printf_fd(fd, "error");
	if (command->error_name)
		ft_printf_fd(fd, ": %s", command->error_name);
	ft_printf_fd(fd, "\n");
}
