/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 14:14:28 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/28 11:24:09 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include "sh21.h"
#include "sh42.h"
#include <dirent.h>
#include "toolkit.h"
#include "globbing.h"

t_item		*get_dir_items(char *path, char *chr)
{
	t_item			*items;
	DIR				*dir_chr;
	struct dirent	*cur_item;

	items = NULL;
	dir_chr = opendir(path);
	if (chr && ft_strcmp(chr, "") == 0)
		chr = NULL;
	if (dir_chr)
	{
		while ((cur_item = readdir(dir_chr)) && cur_item)
			if (is_valid_item(chr, cur_item->d_name))
				t_item_place(&items, t_item_new(cur_item->d_name));
		link_loop(items);
	}
	if (dir_chr)
		closedir(dir_chr);
	return (items);
}

t_item		*get_commands_items(char **env, char *chr)
{
	t_item			*items;
	DIR				*dir_chr;
	struct dirent	*cur_item;
	char			**bin_paths;
	int				i;

	items = NULL;
	i = -1;
	bin_paths = ft_strsplit(find_env(env, "PATH"), ':');
	if (chr && IS_COMMAND_START(*chr))
		chr = NULL;
	while (bin_paths[++i])
	{
		dir_chr = opendir(bin_paths[i]);
		if (dir_chr)
			while ((cur_item = readdir(dir_chr)) && cur_item)
				if (is_valid_item(chr, cur_item->d_name))
					t_item_place(&items, t_item_new(cur_item->d_name));
		if (dir_chr)
			closedir(dir_chr);
	}
	if (bin_paths)
		ft_freetab(bin_paths);
	link_loop(items);
	return (items);
}

char		*replace_tild_completion(t_shprop *shell, char **path)
{
	char	*homedir;
	t_shell	*sh;

	sh = (t_shell *)shell->sh_ptr;
	homedir = NULL;
	if (**path && ft_strncmp(*path, "~/", 2) == 0)
	{
		homedir = find_env(sh->env, "HOME");
		if (homedir)
		{
			if (homedir[ft_strlen(homedir) - 1] != '/')
				homedir = ft_strjoin(homedir, "/");
			else
				homedir = ft_strdup(homedir);
			*path = ft_replace(*path, "~/", homedir);
			ft_strdel(&homedir);
		}
	}
	return (*path);
}

int			search_in_dir(t_shprop *shell, char *chr)
{
	char	*path;
	int		index_cut;
	char	*to_chr;
	int		match_ret;

	index_cut = ft_index_lmatch(chr, '/');
	to_chr = NULL;
	if (index_cut != -1)
	{
		to_chr = ft_strsub(chr, index_cut + 1, ft_strlen(chr) - index_cut - 1);
		path = ft_strsub(chr, 0, index_cut + 1);
	}
	else
	{
		path = ft_strdup("./");
		if (*chr)
			to_chr = ft_strdup(chr);
	}
	replace_tild_completion(shell, &path);
	match_ret = match_chr(shell, path, to_chr);
	free(path);
	free(to_chr);
	return (match_ret);
}
