/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 14:26:39 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/23 13:45:19 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static void	ft_one_star(char **str)
{
	char	*temp;
	int		i;
	int		y;

	y = 0;
	i = 0;
	temp = *str;
	*str = (char*)malloc((ft_strlen(temp) + 1) * sizeof(char));
	while (temp[i])
	{
		str[0][y] = temp[i];
		if (temp[i] == '*')
		{
			while (temp[i] == '*')
				i++;
			i--;
		}
		y++;
		i++;
	}
	str[0][y] = '\0';
	free(temp);
}

static void	recollage(char **res, char *str)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	if (res != NULL)
	{
		while (res[i] != NULL)
		{
			temp = ft_strdup(res[i]);
			free(res[i]);
			res[i] = ft_strjoin(temp, str);
			free(temp);
			i++;
		}
	}
	free(str);
}

static int	search_globbing(char **str)
{
	int	i;
	int	y;

	i = 0;
	while (str[i] != NULL)
	{
		y = 0;
		while (str[i][y])
		{
			if (ft_strchr("*[?", str[i][y]) != NULL)
				return (i);
			y++;
		}
		i++;
	}
	return (-1);
}

static char	**file_splitting(char **str, int pos)
{
	int		i;
	char	*save;
	char	**res;

	i = 0;
	ft_one_star(str);
	while (str[pos][i] && ft_strchr("*?[{", str[pos][i]) == NULL)
		i++;
	while (str[pos][i] && str[pos][i] != '/')
		i++;
	save = ft_strdup(&(str[pos][i]));
	str[pos][i] = '\0';
	res = globbing(str[pos]);
	str[pos][0] = '\0';
	recollage(res, save);
	res = add_double_char(res, str);
	return (res);
}

char		**launch(char *str)
{
	char	**files;
	char	**temp;
	int		pos;

	files = (char**)malloc(2 * sizeof(char*));
	files[0] = ft_strdup(str);
	files[1] = NULL;
	if ((pos = search_globbing(files)) == -1)
	{
		temp = split_accolades(files[0]);
		free_double_char(files);
		return (temp);
	}
	if (check_error(str) == 0)
	{
		free(files[0]);
		files[0] = NULL;
		return (files);
	}
	while ((pos = search_globbing(files)) != -1)
		files = file_splitting(files, pos);
	pos = 0;
	files = destroy_empty(files);
	return (files);
}
