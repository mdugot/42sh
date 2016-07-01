/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 18:59:59 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 17:46:07 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#define ERR1 "Variable name must contain alphanumeric characters."

int		is_correct_varname(char *name, int err, char *cmd)
{
	int i;

	if (ft_isalpha(*name) == 0)
	{
		ft_printf_fd(err, "%s: Variable name must begin with a letter.\n", cmd);
		return (0);
	}
	i = 0;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0)
		{
			ft_printf_fd(err, "%s: %s\n", cmd, ERR1);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**env_add(char **env, char *var, char *content)
{
	char	**result;
	char	*new;
	int		i;
	int		n;

	if (find_env(env, var))
		return (env_replace(env, var, content));
	n = 0;
	while (env[n])
		n++;
	result = secure_alloc(sizeof(char*) * (n + 2));
	i = -1;
	while (++i < n)
		result[i] = env[i];
	if (content == NULL)
		new = ft_strf("%s=", var);
	else
		new = ft_strf("%s=%s", var, content);
	result[i] = new;
	ft_memdel((void**)&env);
	return (result);
}

char	**env_copy(char **env)
{
	char	**result;
	int		i;
	int		n;

	n = 0;
	while (env[n])
		n++;
	result = secure_alloc(sizeof(char*) * (n + 1));
	i = 0;
	while (i < n)
	{
		result[i] = ft_strdup(env[i]);
		i++;
	}
	return (result);
}

void	print_env(char **env, int out)
{
	int i;

	if (env == NULL)
		return ;
	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], out);
		i++;
	}
}

char	**env_delete(char **env, char *to_delete)
{
	char	**result;
	int		i;
	int		j;
	int		n;

	if (find_env(env, to_delete) == NULL)
		return (env);
	n = 0;
	while (env[n])
		n++;
	result = secure_alloc(sizeof(char*) * n);
	i = 0;
	j = 0;
	while (i < n)
	{
		if (env_cmp(env[i], to_delete) != 0)
		{
			result[j] = ft_strdup(env[i]);
			j++;
		}
		ft_strdel(&env[i]);
		i++;
	}
	ft_memdel((void**)&env);
	return (result);
}
