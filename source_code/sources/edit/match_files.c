/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 15:43:14 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/24 17:23:34 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "toolkit.h"
#include "sh21.h"

t_item		*t_item_new(char *name)
{
	t_item *new;

	new = (t_item *)malloc(sizeof(t_item));
	if (new)
	{
		new->item_name = ft_strdup(name);
		new->select = 0;
		new->ind = 0;
		new->prev = NULL;
		new->next = NULL;
	}
	return (new);
}

void		t_item_push(t_item **items, t_item *new)
{
	t_item *index;

	index = *items;
	if (!index)
	{
		*items = new;
		new->prev = new;
		new->ind = 1;
	}
	else
	{
		index->ind = 1;
		while (index->next)
			index = index->next;
		index->last = 0;
		index->next = new;
		new->prev = index;
	}
}

void		link_loop(t_item *first)
{
	t_item	*index;

	if (first)
	{
		index = first;
		while (index->next)
			index = index->next;
		index->last = 1;
		index->next = first;
		first->prev = index;
	}
}

void		free_cur_item(t_item *cur)
{
	free(cur->item_name);
	free(cur);
}
