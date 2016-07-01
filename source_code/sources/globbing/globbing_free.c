/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 21:58:24 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 22:00:33 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		free_and_quit(char *str)
{
	free(str);
	return (0);
}

char	**free_and_quit_null(char *str)
{
	free(str);
	return (NULL);
}