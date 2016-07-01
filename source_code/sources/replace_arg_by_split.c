/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_arg_by_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 09:04:54 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 09:04:55 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char			**replace_in_new(int i, int *j, char **new, char **split)
{
	int		split_size;

	split_size = ft_strsplit_size(split);
	while (*j < split_size)
	{
		new[i + *j] = split[*j];
		(*j)++;
	}
	(*j)--;
	return (new);
}

static char			**fill_new_arg(char **old, const char *arg, char **split,
							char **new)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] != arg)
			new[i + j] = old[i];
		else
			new = replace_in_new(i, &j, new, split);
		i++;
	}
	return (new);
}

char				**replace_arg_by_split(char **old, char *arg, char **split)
{
	char	**new;
	int		split_size;
	int		new_argc;

	split_size = ft_strsplit_size(split);
	new_argc = ft_strsplit_size(old) - 1 + split_size;
	new = ft_memalloc(sizeof(char*) * (new_argc + 1));
	new = fill_new_arg(old, arg, split, new);
	ft_strdel(&arg);
	ft_memdel((void**)&split);
	ft_memdel((void**)&old);
	return (new);
}
