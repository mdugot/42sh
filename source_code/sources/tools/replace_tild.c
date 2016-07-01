/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tild.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 14:08:16 by mressier          #+#    #+#             */
/*   Updated: 2016/06/29 17:46:05 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*get_prefix(char *temp)
{
	int				i;
	struct passwd	*user;

	i = 0;
	while (temp[i] && temp[i] != '/')
		i++;
	temp[i] = '\0';
	user = getpwnam(&(temp[1]));
	if (user)
		return (user->pw_dir);
	else
		return (NULL);
}

char			*replace_tild(char **env, char *str)
{
	char			*prefix;
	char			*ret;
	char			*temp;

	temp = ft_strdup(str);
	if (temp[1] == '/' || temp[1] == '\0')
		prefix = find_env(env, "HOME");
	else
	{
		prefix = get_prefix(temp);
		if (prefix == NULL)
		{
			ft_strdel(&temp);
			return (ft_strdup(str));
		}
	}
	while (str[0] && *str != '/')
		str++;
	if (prefix)
		ret = ft_strjoin(prefix, str);
	else
		ret = ft_strdup(temp);
	ft_strdel(&temp);
	return (ret);
}
