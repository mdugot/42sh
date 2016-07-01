/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 20:11:06 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/15 20:18:33 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static void	init(int *i, int *y, int *bool)
{
	*i = 0;
	*y = 0;
	*bool = 0;
}

static void	thanks_norme(int *i, int *y, char *temp, char *str)
{
	while (str[*i + 1] == '*' && str[*i + 2] == '/')
	{
		temp[*y + 1] = '*';
		temp[*y + 2] = '/';
		*y = *y + 2;
		*i = *i + 2;
	}
}

char		*ft_insert(char *str)
{
	char	*temp;
	int		i;
	int		y;
	int		bool;

	init(&i, &y, &bool);
	temp = (char*)malloc((ft_strlen(str) + 3) * sizeof(char));
	while (str[i] && bool == 0)
	{
		temp[y] = str[i];
		if (temp[y] == '/' && y > 1 && temp[y - 1] == '*' && temp[y - 2] == '*')
		{
			temp[y + 1] = '*';
			temp[y + 2] = '/';
			y = y + 2;
			bool = 1;
			thanks_norme(&i, &y, temp, str);
			temp[y] = '\0';
		}
		y++;
		i++;
	}
	return (temp);
}
