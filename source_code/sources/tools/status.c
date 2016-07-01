/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 14:11:28 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 14:11:29 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

int		exit_status(int status, t_shell *sh)
{
	if (WIFEXITED(status))
	{
		sh->last_status_type = ST_NORMAL;
		sh->last_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		sh->last_status_type = ST_SIGNAL;
		sh->last_status = WTERMSIG(status);
	}
	else if (WIFSTOPPED(status))
	{
		sh->last_status_type = ST_STOP;
		sh->last_status = WSTOPSIG(status);
	}
	else
	{
		sh->last_status_type = -1;
		sh->last_status = -1;
	}
	change_status(sh, sh->last_status);
	return (sh->last_status);
}

void	change_status(t_shell *sh, int n)
{
	char	*tmp;

	sh->last_status = n;
	tmp = ft_itoa(n);
	sh->local = env_add(sh->local, "?", tmp);
	ft_strdel(&tmp);
}
