/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 11:13:14 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/28 11:18:12 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <sys/stat.h>
#include "sh21.h"
#include "sh42.h"
#include <dirent.h>
#include "toolkit.h"
#include "globbing.h"

int			get_one_input(void)
{
	char	*buf[5];

	ft_bzero(buf, 5);
	if (read(0, buf, 4) == -1)
		return (-1);
	return ((int)*buf);
}

void		replace_and_print_completed(t_shprop *shell, char *new,
		size_t len, int video_mode)
{
	t_term *term;

	term = shell->term;
	while (shell->input[shell->curs_pos])
	{
		if (shell->input[shell->curs_pos] == ' ')
			break ;
		key_move_right(shell);
	}
	len++;
	while (--len)
		key_delete_char(shell);
	while (shell->input && len == 0)
	{
		if (shell->input[shell->curs_pos - 1] == ' '
				|| shell->input[shell->curs_pos - 1] == '/'
				|| IS_COMMAND_START(shell->input[shell->curs_pos - 1]))
			break ;
		key_delete_char(shell);
	}
	if (video_mode == 1)
		T_SETMODE("mr");
	insert_line_on_shell(shell, new);
	T_SETMODE("me");
}

int			complete_by_glob(t_shprop *shell, char *exp)
{
	char	**ret;
	char	*imploded;

	ret = ft_glob(exp);
	imploded = NULL;
	if (ret && *ret && (ft_strcmp(ret[0], exp) != 0))
	{
		imploded = ft_implode(ret, " ");
		replace_and_print_completed(shell, imploded, ft_strlen(exp), 0);
		free(imploded);
	}
	if (ret)
		ft_freetab(ret);
	return (1);
}

t_item		*t_item_place(t_item **first, t_item *new)
{
	t_item *index;

	index = NULL;
	if (new)
	{
		if (*first)
			index = *first;
		if (!index)
		{
			*first = new;
			return (*first);
		}
		else if (ft_strcmp(new->item_name, index->item_name) < 0)
		{
			new->next = index;
			*first = new;
			return (new);
		}
		else
			index->next = t_item_place(&index->next, new);
	}
	return (index);
}

int			is_valid_item(char *chr, char *item_name)
{
	if (!chr || ft_strncmp(item_name, chr, ft_strlen(chr)) == 0)
	{
		if (chr || (!chr && *item_name != '.'))
			if (ft_strcmp(item_name, ".") != 0
					&& ft_strcmp(item_name, "..") != 0)
				return (1);
	}
	return (0);
}
