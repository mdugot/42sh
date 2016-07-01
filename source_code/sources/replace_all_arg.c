/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 08:50:58 by mressier          #+#    #+#             */
/*   Updated: 2016/06/29 21:30:05 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	**replace_all_arg(char **sp, t_shell *sh, t_command *c)
{
	int			i;
	char		*tmp;

	if (!sp)
		return (sp);
	i = 0;
	while (sp[i])
	{
		tmp = replace_variable(sp[i], sh);
		ft_strdel(&sp[i]);
		sp[i] = ft_strdup(tmp);
		ft_strdel(&tmp);
		i++;
	}
	i = -1;
	while (sp[++i])
		if (ft_strchr(sp[i], '$'))
		{
			command_error(c, "Undefined variable", ft_strchr(sp[i], '$') + 1);
			return (sp);
		}
	sp = replace_arg_by_subshell(sp, sh);
	sp = replace_arg_by_globbing(sp, c);
	return (sp);
}
