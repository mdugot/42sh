/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:31:24 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/28 10:32:41 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh42.h"

void			goto_begin_args(t_cmd_param **params)
{
	while (*params && (*params)->prev)
		(*params) = (*params)->prev;
}

int				find_existing_param(t_cmd_param **params, char *chr)
{
	t_cmd_param *bak;

	bak = *params;
	goto_begin_args(params);
	while (*params)
	{
		if (ft_strcmp((*params)->param, chr) == 0)
			return (1);
		(*params) = (*params)->next;
	}
	*params = bak;
	return (0);
}
