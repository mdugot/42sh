/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:48:58 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/25 16:22:48 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			read_redirection(t_shell *sh, t_command *c, char **split, int i)
{
	int		r;

	(void)sh;
	r = 0;
	if (ft_strncmp(split[i], ">>", ft_strlen(">>")) == 0)
		add_redirection_out(c, 1, r_argument(split, i, ">>", &r), 1);
	else if (ft_strncmp(split[i], "<<", ft_strlen("<<")) == 0)
		add_redirection_in(c, 0, r_argument(split, i, "<<", &r), 1);
	else if (ft_strncmp(split[i], "<", ft_strlen("<")) == 0)
		add_redirection_in(c, 0, r_argument(split, i, "<", &r), 0);
	else if (ft_strncmp(split[i], ">", ft_strlen(">")) == 0)
		add_redirection_out(c, 1, r_argument(split, i, ">", &r), 0);
	return (r);
}

char		*r_argument(char **split, int i, char *name, int *r)
{
	static char	*tmp = NULL;
	char		*next_arg;

	(void)name;
	ft_strdel(&tmp);
	if (split == NULL)
		return (NULL);
	*r = 1;
	next_arg = split[i + 1];
	if (next_arg && is_redirection(&next_arg))
		return (NULL);
	if (next_arg)
		*r = 2;
	tmp = unprotect(ft_strdup(next_arg));
	return (tmp);
}
