/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:14:16 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/25 17:10:39 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

char		*find_env(char **env, char *name)
{
	int		i;
	char	*result;

	i = 0;
	while (env[i] != NULL)
	{
		if (env_cmp(env[i], name) == 0)
		{
			result = env[i];
			while (*result && *result != '=')
				result++;
			if (!*result)
				return (NULL);
			else
				result++;
			return (result);
		}
		i++;
	}
	return (NULL);
}
