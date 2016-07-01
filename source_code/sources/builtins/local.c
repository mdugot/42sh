/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 15:17:16 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 17:20:48 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		**add_split(char **sa, char **sb)
{
	int		lena;
	int		lenb;
	char	**result;
	int		i;
	int		j;

	lena = ft_strsplit_size(sa);
	lenb = ft_strsplit_size(sb);
	result = ft_memalloc(sizeof(char*) * (lena + lenb + 1));
	i = 0;
	j = 0;
	while (sa[i])
	{
		result[j] = sa[i];
		i++;
		j++;
	}
	i = 0;
	while (sb[i])
	{
		result[j] = sb[i];
		i++;
		j++;
	}
	return (result);
}

char		**sort_split(char **env)
{
	int		i;
	char	*tmp;
	int		len;
	int		before_len;

	i = 0;
	while (env[i])
	{
		len = ft_strchr(env[i], '=') - env[i];
		if (i > 0)
			before_len = ft_strchr(env[i - 1], '=') - env[i - 1];
		if (i > 0 && len > before_len)
		{
			tmp = env[i];
			env[i] = env[i - 1];
			env[i - 1] = tmp;
			i--;
		}
		else
			i++;
	}
	i = 0;
	return (env);
}

static char	*is_tild(char *line, t_shell *sh)
{
	char	*tmp;

	tmp = NULL;
	if (*line == '~')
	{
		tmp = replace_tild(sh->env, line);
		line = tmp;
		tmp = NULL;
	}
	else
		line = ft_strdup(line);
	return (line);
}

char		*replace_variable(char *line, t_shell *sh)
{
	char	*name;
	char	*value;
	char	**tmp;
	int		i;
	int		len;

	line = is_tild(line, sh);
	if (ft_strchr(line, '$') == NULL)
		return (line);
	i = 0;
	tmp = sort_split(add_split(sh->env, sh->local));
	while (tmp[i])
	{
		len = 0;
		while (tmp[i][len] != '=')
			len++;
		name = ft_strf("$%.*s", len, tmp[i]);
		value = &tmp[i][len + 1];
		line = replace_out(line, name, value, "'");
		ft_strdel(&name);
		i++;
	}
	ft_memdel((void**)&tmp);
	return (line);
}
