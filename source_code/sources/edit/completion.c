/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 11:14:46 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/28 11:14:47 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include "sh21.h"
#include "sh42.h"
#include <dirent.h>
#include "toolkit.h"
#include "globbing.h"

t_item			*select_mode_search(t_shprop *shell, char *path, char *chr)
{
	int		i;

	i = shell->curs_pos;
	if (shell->input)
	{
		while ((i > 0 && shell->input[i - 1]) && shell->input[i] != ' '
				&& IS_COMMAND_START(shell->input[i - 1]) == 0)
		{
			if (shell->input[i] == '/')
				return (get_dir_items(path, chr));
			i--;
		}
		while (((i > 0 && shell->input[i - 1]) && shell->input[i] == ' ')
				&& IS_COMMAND_START(shell->input[i - 1]) == 0)
			i--;
		if (i <= 0 || IS_COMMAND_START(shell->input[i - 1]))
			return (get_commands_items(shell->env, chr));
		else
			return (get_dir_items(path, chr));
	}
	else
		return (get_commands_items(shell->env, NULL));
}

int				free_match_vars(t_item *items, char **comp, int ret)
{
	t_item *next;

	next = NULL;
	ft_strdel(comp);
	if (items)
	{
		next = items;
		items = items->next;
		next->next = NULL;
		while (items)
		{
			next = items->next;
			free_cur_item(items);
			items = next;
		}
	}
	return (ret);
}

char			*complete_name_type_file(char *path, t_item *item)
{
	struct stat		prop;
	char			*complete;
	char			*new;

	complete = ft_strjoin(path, item->item_name);
	if (lstat(complete, &prop) != -1 && S_ISDIR(prop.st_mode))
		new = ft_strjoin(item->item_name, "/");
	else
		new = ft_strjoin(item->item_name, " ");
	ft_strdel(&complete);
	return (new);
}
