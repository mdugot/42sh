/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_annexe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 20:38:41 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/15 20:49:52 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

char	*create_save(char *str)
{
	int		bool;
	int		i;
	char	*ret;

	i = 0;
	bool = 1;
	while (str[i] && bool == 1)
	{
		if (str[i] == '*' && str[i + 1] == '*' && str[i + 2] == '/')
		{
			i = i + 2;
			while (str[i + 1] == '*' && str[i + 2] == '/')
				i = i + 2;
			bool = 0;
		}
		i++;
	}
	i--;
	ret = ft_strdup(&(str[i]));
	str[i] = '\0';
	return (ret);
}

void	recursion_recollage(char **files, char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while (files[i] != NULL)
	{
		temp = ft_strdup(files[i]);
		free(files[i]);
		files[i] = ft_strjoin(temp, str);
		free(temp);
		i++;
	}
	free(str);
}

int		detect_double(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '*' && str[i + 1] &&
			str[i + 1] == '*' && str[i + 2] == '/')
			count++;
		i++;
	}
	return (count);
}
