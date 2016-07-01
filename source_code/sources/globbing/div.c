/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:23:12 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/21 14:11:40 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char	**init_destroy_empty(int *i, int *y, char **str)
{
	char **new;

	*i = -1;
	*y = 0;
	new = (char**)malloc((get_size_double_char(str) + 1) * sizeof(char*));
	return (new);
}

int			ft_glob_strlen(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '[')
		{
			while (str[i] != ']')
				i++;
		}
		i++;
		count++;
	}
	return (count);
}

void		print_double_char(char **str)
{
	int		i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != NULL)
		{
			ft_putstr("indice ");
			ft_putnbr(i);
			ft_putstr(" : ");
			ft_putendl(str[i]);
			i++;
		}
	}
}

char		**destroy_empty(char **str)
{
	char	**new;
	char	*tmp;
	int		i;
	int		y;

	new = init_destroy_empty(&i, &y, str);
	while (str[++i] != NULL && ((tmp = str[i]) != NULL))
	{
		if (ft_strchr(tmp, '\033'))
			tmp = unprotect(ft_strdup(str[i]));
		if (access(tmp, F_OK) != 0)
			str[i][0] = '\0';
		if (tmp != str[i])
			ft_strdel(&tmp);
	}
	i = -1;
	while (str[++i] != NULL)
		if (str[i][0] != '\0')
		{
			new[y] = ft_strdup(str[i]);
			y++;
		}
	new[y] = NULL;
	free_double_char(str);
	return (new);
}

void		kill_star_in_brackets(char **str)
{
	char	*temp;
	int		i;
	int		y;
	int		pos;

	i = 0;
	y = 0;
	pos = 0;
	temp = *str;
	*str = (char*)malloc((ft_strlen(temp) + 1) * sizeof(char));
	while (temp[i])
	{
		if (temp[i] == '[')
			pos++;
		if (temp[i] == ']')
			pos--;
		while (temp[i] == '*' && pos > 0)
			i++;
		str[0][y] = temp[i];
		i++;
		y++;
	}
	str[0][y] = '\0';
	free(temp);
}
