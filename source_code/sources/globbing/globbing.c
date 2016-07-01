/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 14:04:10 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/29 22:05:53 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int	open_directory(DIR **mydir, char **str, char **save)
{
	int		i;

	i = 0;
	*mydir = NULL;
	if ((ft_strchr(*str, '/') == NULL) && (*save = ft_strdup(".")) != NULL)
	{
		if ((*mydir = opendir("./")) == NULL)
			return (free_and_quit(*save));
	}
	else
	{
		*save = ft_strdup(*str);
		while (save[0][i])
			i++;
		while (save[0][i] != '/')
			i--;
		if (i == 0)
			*mydir = opendir("/");
		save[0][i] = '\0';
		if ((*mydir == NULL) && ((*mydir = opendir(*save)) == NULL))
			return (free_and_quit(*save));
		free(*str);
		*str = ft_strdup(&(save[0][i + 1]));
	}
	return (1);
}

static void	recollage(char **splitted, char *save)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	if (ft_strcmp(save, ".") != 0)
	{
		while (splitted[i] != NULL)
		{
			temp = ft_strjoin(save, "/");
			temp2 = ft_strjoin(temp, splitted[i]);
			free(splitted[i]);
			free(temp);
			splitted[i] = ft_strdup(temp2);
			free(temp2);
			i++;
		}
	}
	free(save);
}

void		globbing_loop(t_dir_ext direc, t_list_glob **lst, char **splitted)
{
	int				i;
	char			*tmp;

	i = -1;
	tmp = (direc.lecture)->d_name;
	if (has_syntax_in(tmp))
		tmp = protect_all(ft_strdup((direc.lecture)->d_name));
	while (splitted[++i] != NULL)
	{
		if (meta_glob_cmp(splitted[i], tmp) == 1)
			add_lst(lst, tmp);
	}
	if (tmp != (direc.lecture)->d_name)
		ft_strdel(&tmp);
}

char		**globbing(char *str)
{
	t_dir_ext		direc;
	t_list_glob		*lst;
	char			**splitted;
	char			*old;

	old = ft_strdup(str);
	kill_star_in_brackets(&old);
	lst = NULL;
	if (open_directory(&(direc.mydir), &old, &(direc.save)) == 0)
		return (free_and_quit_null(old));
	splitted = split_accolades(old);
	while ((direc.lecture = readdir(direc.mydir)) != NULL)
		globbing_loop(direc, &lst, splitted);
	closedir(direc.mydir);
	free_double_char(splitted);
	splitted = conversion(&lst);
	recollage(splitted, direc.save);
	free(old);
	return (splitted);
}
