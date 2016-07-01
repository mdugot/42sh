/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accolades.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 17:18:39 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/28 12:18:08 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static void	ft_parsing_3(char **str, int *i, int count)
{
	while (str[0][*i] && count > 0)
	{
		if (str[0][*i] == '{')
			count++;
		else if (str[0][*i] == '}')
			count--;
		(*i)++;
	}
}

static char	*ft_parsing_2(char *str, char *cpy, int i, int y)
{
	int	count;

	count = 1;
	while (str[i] && !(str[i] == ',' && count == 1) && count > 0)
	{
		if (str[i] == '{')
			count++;
		else if (str[i] == '}')
			count--;
		if (count > 0)
			cpy[y] = str[i];
		i++;
		y++;
	}
	ft_parsing_3(&str, &i, count);
	while (str[i])
	{
		cpy[y] = str[i];
		i++;
		y++;
	}
	cpy[y] = '\0';
	return (cpy);
}

static char	*ft_parsing(char *str, int pos)
{
	char	*cpy;
	int		i;
	int		y;

	i = 0;
	y = 0;
	cpy = (char*)malloc((ft_strlen(str) + 1) * sizeof(char));
	while (str[i] && str[i] != '{')
	{
		cpy[y] = str[i];
		y++;
		i++;
	}
	i++;
	while (str[i] && pos != 0)
	{
		if (str[i] == ',')
			pos--;
		i++;
	}
	return (ft_parsing_2(str, cpy, i, y));
}

static char	**transform(char *str, int i)
{
	char	**res;
	int		y;
	int		position;

	position = 0;
	y = 0;
	res = NULL;
	while (str[i] && res == NULL)
	{
		if (str[i] == '{')
			res = (char**)malloc((get_size_accolade(&(str[i])) + 1)
			* sizeof(char*));
		else
			i++;
	}
	while (y < get_size_accolade(&(str[i])))
	{
		res[y] = ft_parsing(str, position);
		position++;
		y++;
	}
	res[y] = NULL;
	str[0] = '\0';
	return (res);
}

char		**split_accolades(char *str)
{
	char	**listing;
	char	**temp;
	int		pos;

	listing = (char**)malloc(2 * sizeof(char*));
	listing[0] = ft_strdup(str);
	listing[1] = NULL;
	while ((pos = verif_accolades(listing)) != -1)
	{
		temp = transform(listing[pos], 0);
		listing = add_double_char(listing, temp);
	}
	return (listing);
}
