/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 17:43:42 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 17:43:44 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			read_fd(t_shell *sh, t_command *c, char **s, int i)
{
	int		r;
	int		id;
	char	*tmp;

	r = 0;
	tmp = s[i];
	if ((id = read_positive_number(&tmp, 256)) >= 0)
	{
		if (ft_strncmp(tmp, ">>", ft_strlen(">>")) == 0)
			add_redirection_out(c, id, r_argument(s, i, "*>>", &r), 1);
		else if (ft_strncmp(tmp, "<<", ft_strlen("<<")) == 0)
			add_redirection_in(c, id, r_argument(s, i, "*<<", &r), 1);
		else if (ft_strncmp(tmp, "<>", ft_strlen("<>")) == 0)
		{
			add_redirection_in(c, id, r_argument(s, i, "*<>", &r), 0);
			add_redirection_out(c, id, r_argument(s, i, "*<>", &r), -1);
		}
		else if (ft_strncmp(tmp, "<", ft_strlen("<")) == 0)
			add_redirection_in(c, id, r_argument(s, i, "*<", &r), 0);
		else if (ft_strncmp(tmp, ">", ft_strlen(">")) == 0)
			add_redirection_out(c, id, r_argument(s, i, "*>", &r), 0);
	}
	return (r == 0 ? read_redirection(sh, c, s, i) : r);
}
