/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_subshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 15:19:00 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 15:55:11 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/wait.h>

static char		*do_str_subshell(int fd)
{
	char	*result;
	char	*tmp;
	char	buff[1001];
	int		r;

	result = ft_strdup("");
	while ((r = read(fd, buff, 1000)) > 0)
	{
		buff[r] = 0;
		tmp = ft_strjoin(result, buff);
		ft_strdel(&result);
		result = tmp;
	}
	return (result);
}

static void		child_subshell(int pip[2], t_shell *shell, char *line)
{
	int		old_out;

	close(pip[0]);
	old_out = dup(1);
	dup2(pip[1], 1);
	do_subshell(shell, line, 0);
	close(pip[1]);
	dup2(old_out, 1);
	exit(shell->last_status);
}

static char		*parent_subshell(int pip[2], t_shell *shell, int child)
{
	int		signal;
	char	*result;

	close(pip[1]);
	result = do_str_subshell(pip[0]);
	close(pip[0]);
	waitpid(child, &signal, 0);
	change_status(shell, exit_status(signal, shell));
	return (result);
}

char			*str_subshell(char *line, t_shell *shell)
{
	int		pip[2];
	int		child;
	char	*result;

	pipe(pip);
	child = my_fork();
	if (child == 0)
	{
		child_subshell(pip, shell, line);
		return (NULL);
	}
	else
	{
		result = parent_subshell(pip, shell, child);
		return (result);
	}
}
