/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 16:08:56 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/15 15:15:58 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "sh21.h"
#include "history.h"

void	free_shprop(t_shprop **shprop)
{
	int	i;

	clear_history(&(*shprop)->hist);
	i = 0;
	while ((*shprop)->env != NULL && (*shprop)->env[i])
	{
		ft_strdel(&(*shprop)->env[i]);
		i++;
	}
	ft_memdel((void **)(*shprop)->env);
	if ((*shprop)->prompt)
		free((*shprop)->prompt);
	if ((*shprop)->input)
		free((*shprop)->input);
	free(*shprop);
}
