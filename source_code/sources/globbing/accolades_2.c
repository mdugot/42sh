/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accolades_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 14:46:14 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/23 10:52:20 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

int			verif_accolades(char **listing)
{
	int		i;
	int		y;

	i = 0;
	while (listing[i] != NULL)
	{
		y = 0;
		while (listing[i][y])
		{
			if (listing[i][y] == '{')
				return (i);
			y++;
		}
		i++;
	}
	return (-1);
}

int			get_size_accolade(char *accolade)
{
	int		i;
	int		count;
	int		count_acc;

	i = 1;
	count = 1;
	count_acc = 1;
	while (accolade[i] != '\0' && count_acc > 0)
	{
		if (accolade[i] == ',' && count_acc == 1)
			count++;
		else if (accolade[i] == '{')
			count_acc++;
		else if (accolade[i] == '}')
			count_acc--;
		i++;
	}
	return (count);
}
