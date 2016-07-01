/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 10:34:05 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 10:34:06 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*join_paths(char *base_path, char *to_add)
{
	char	*logic_cwd;

	logic_cwd = ft_strnew(ft_strlen(base_path) + ft_strlen(to_add) + 2);
	ft_strcat(logic_cwd, base_path);
	if (base_path[ft_strlen(base_path) - 1] != '/' && *to_add)
		ft_strcat(logic_cwd, "/");
	ft_strcat(logic_cwd, to_add);
	return (logic_cwd);
}
