/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 20:12:47 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/16 13:36:09 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		env_free(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_strdel(&env[i]);
		i++;
	}
	ft_memdel((void**)&env);
}

int			env_cmp(char *var_con, char *var)
{
	if (ft_strncmp(var_con, var, ft_strlen(var)) == 0)
	{
		if (var_con[ft_strlen(var)] == '=')
			return (0);
	}
	return (-1);
}

char		**env_replace(char **env, char *var, char *content)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (env_cmp(env[i], var) == 0)
		{
			ft_strdel(&env[i]);
			env[i] = ft_strf("%s=%s", var, content);
		}
		i++;
	}
	return (env);
}

char		**env_arg(char *arg, char **env)
{
	char	*tmp1;
	char	*tmp2;
	char	**result;

	tmp1 = ft_strdup(arg);
	if ((tmp2 = ft_strchr(tmp1, '=')) == NULL)
	{
		ft_strdel(&tmp1);
		return (env);
	}
	*tmp2 = '\0';
	tmp2++;
	result = env;
	result = env_add(result, tmp1, tmp2);
	ft_strdel(&tmp1);
	return (result);
}

char		**update_shlvl(char **env)
{
	char	**result;
	char	*shlvl;
	char	*tmp;
	int		n;

	shlvl = find_env(env, "SHLVL");
	if (shlvl == NULL)
		return (env_add(env, "SHLVL", "1"));
	if (!ft_isint(shlvl, &n))
		return (env);
	n++;
	tmp = ft_itoa(n);
	result = env_add(env, "SHLVL", tmp);
	ft_strdel(&tmp);
	return (result);
}
