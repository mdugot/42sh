/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_chr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:48:14 by mressier          #+#    #+#             */
/*   Updated: 2016/06/29 11:48:16 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*get_complete_and_up_delete_len(char *path, t_item *item,
					t_shprop *shell, int *delete_len)
{
	char		*complete;

	complete = complete_name_type_file(path, item);
	replace_and_print_completed(shell, complete, *delete_len, 0);
	*delete_len = ft_strlen(complete);
	return (complete);
}

static int		get_key_input(t_shprop *shell, char *complete, int del_len)
{
	int		key_input;

	replace_and_print_completed(shell, complete, del_len, 1);
	key_input = get_one_input();
	if (key_input == -1)
		return (0);
	replace_and_print_completed(shell, complete, del_len, 0);
	if (key_input == RETURN_KEY)
		return (1);
	else if (key_input != 9)
		return (-1);
	return (2);
}

int				match_chr(t_shprop *shell, char *path, char *chr)
{
	t_item			*item;
	int				key_input;
	char			*complete;
	int				del_len;

	complete = NULL;
	del_len = 0;
	item = select_mode_search(shell, path, chr);
	while (item)
	{
		complete = get_complete_and_up_delete_len(path, item, shell, &del_len);
		if (item == item->next)
			return (free_match_vars(item, &complete, 1));
		key_input = get_key_input(shell, complete, del_len);
		if (key_input == -1)
			break ;
		else if (key_input == 0 || key_input == 1)
			return (free_match_vars(item, &complete, key_input));
		item = item->next;
		ft_strdel(&complete);
	}
	if (!item)
		return (free_match_vars(item, &complete, 0));
	return (free_match_vars(item, &complete, key_input));
}
