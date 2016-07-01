/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 12:32:13 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 12:32:14 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_shell		*new_shell(char **env, t_shprop *edit)
{
	t_shell *result;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		cwd = ft_strdup(".");
	result = secure_alloc(sizeof(t_shell));
	result->env = env_copy(env);
	result->env = env_add(result->env, "SHELL", "42sh");
	result->env = update_shlvl(result->env);
	result->local = ft_memalloc(sizeof(char*));
	result->save_out = dup(1);
	result->save_in = dup(0);
	result->save_error = dup(2);
	result->cwd = cwd;
	shell_adress(result);
	result->edit = edit;
	change_status(result, 0);
	return (result);
}
