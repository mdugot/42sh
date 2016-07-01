/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_aggregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 17:24:53 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 17:24:55 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int			suite_read_aggregation(char **split, int i, t_command *c)
{
	char	*tmp;
	int		r;

	r = 0;
	tmp = split[i];
	if (read_positive_number(&tmp, 256) >= 0)
	{
		if (ft_strncmp(tmp, "<&", ft_strlen("<&")) == 0)
			add_aggregation(c, DT_NULL, r_argument(split, i, "<&", &r));
		if (ft_strncmp(tmp, ">&", ft_strlen(">&")) == 0)
			add_aggregation(c, DT_NULL, r_argument(split, i, ">&", &r));
	}
	return (r);
}

int					read_aggregation(t_shell *sh, t_command *c,
						char **split, int i)
{
	int		r;

	r = 0;
	if (ft_strncmp(split[i], "<&", ft_strlen("<&")) == 0)
		add_aggregation(c, DT_IN, r_argument(split, i, "<&", &r));
	else if (ft_strncmp(split[i], ">&", ft_strlen(">&")) == 0)
		add_aggregation(c, DT_OUT, r_argument(split, i, ">&", &r));
	else if (ft_strncmp(split[i], "0<&", ft_strlen("0<&")) == 0)
		add_aggregation(c, DT_IN, r_argument(split, i, "0<&", &r));
	else if (ft_strncmp(split[i], "1>&", ft_strlen("1>&")) == 0)
		add_aggregation(c, DT_OUT, r_argument(split, i, "1>&", &r));
	else if (ft_strncmp(split[i], "2>&", ft_strlen("2>&")) == 0)
		add_aggregation(c, DT_ERR, r_argument(split, i, "2>&", &r));
	else
		r = suite_read_aggregation(split, i, c);
	if (r == 0)
		return (read_fd(sh, c, split, i));
	else
		return (r);
}
