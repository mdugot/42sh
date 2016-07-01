/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 14:56:36 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/17 15:41:54 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

int		size_list(t_list_glob *lst)
{
	int			i;

	i = 1;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	while (lst->prec != NULL)
		lst = lst->prec;
	return (i);
}

char	**conversion(t_list_glob **lst)
{
	char		**ret;
	int			i;
	t_list_glob *temp;

	ret = (char**)malloc((size_list(*lst) + 1) * sizeof(char*));
	i = 0;
	while ((*lst) != NULL)
	{
		temp = *lst;
		ret[i] = ft_strdup((*lst)->name);
		free((*lst)->name);
		*lst = (*lst)->next;
		free(temp);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int		check_existence(t_list_glob *lst, char *str)
{
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, str) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	add_lst(t_list_glob **lst, char *name)
{
	t_list_glob *new;

	if (check_existence(*lst, name) == 1)
		return ;
	new = (t_list_glob*)malloc(sizeof(t_list_glob));
	new->name = ft_strdup(name);
	new->next = NULL;
	new->prec = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while ((*lst)->next != NULL)
			*lst = (*lst)->next;
		(*lst)->next = new;
		new->prec = (*lst);
		while ((*lst)->prec != NULL)
			*lst = (*lst)->prec;
	}
}
