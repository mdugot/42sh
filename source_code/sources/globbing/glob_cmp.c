/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 14:09:55 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/21 13:59:49 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int	check_end(char *str, char *sub_str)
{
	int i;

	i = (int)ft_glob_strlen(sub_str);
	if (i > (int)ft_strlen(str))
		return (0);
	while (*str)
		str++;
	str = str - i;
	if (glob_strncmp(str, sub_str, ft_strlen(str)) != 0)
		return (0);
	return (1);
}

static int	end_glob_cmp(char **splitted, int i, char *temp, char *str)
{
	while (splitted[i] != NULL)
	{
		if (splitted[i][0])
		{
			str = glob_strstr(str, splitted[i]);
			if (str != NULL)
				str = str + ft_glob_strlen(splitted[i]);
			if (str == NULL)
			{
				free_double_char(splitted);
				return (0);
			}
		}
		i++;
	}
	if (check_end(temp, splitted[i - 1]) == 0)
	{
		free_double_char(splitted);
		return (0);
	}
	free_double_char(splitted);
	return (1);
}

int			glob_cmp(char *wild, char *str)
{
	char	**splitted;
	char	*temp;
	int		i;

	i = 1;
	splitted = ft_explode(wild, "*");
	temp = str;
	if (splitted[0][0])
	{
		if (glob_strncmp(str, splitted[0],
		ft_glob_strlen(splitted[0])) != 0)
		{
			free_double_char(splitted);
			return (0);
		}
	}
	str = str + ft_glob_strlen(splitted[0]);
	return (end_glob_cmp(splitted, i, temp, str));
}

int			meta_glob_cmp(char *wild, char *str)
{
	if ((ft_strcmp(str, ".") != 0) && (ft_strcmp(str, "..") != 0)
	&& ((wild[0] == '.' && str[0] == '.') || (wild[0] != '.' && str[0] != '.')))
	{
		if (ft_strchr(wild, '*') != NULL)
		{
			return (glob_cmp(wild, str));
		}
		if (glob_strncmp(str, wild, ft_strlen(str) + 1) == 0)
		{
			return (1);
		}
	}
	return (0);
}
