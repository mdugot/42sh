/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_decompose.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 15:05:39 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 17:27:31 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				command_error(t_command *c, char *message, char *name)
{
	c->type = C_ERROR;
	if (c->error_message)
		ft_strdel(&c->error_message);
	if (message)
		c->error_message = ft_strdup(message);
	if (c->error_name)
		ft_strdel(&c->error_name);
	if (name)
		c->error_name = ft_strdup(name);
	else
		c->error_name = NULL;
	return (-1);
}

int				is_env_arg(t_command *c, char *arg)
{
	static int	last = 0;

	if (arg == NULL)
	{
		last = 0;
		return (0);
	}
	if (!last && c->argc > 1 && ft_strcmp(c->argv[c->argc - 1], "-u") == 0)
		return (1);
	if (!last && ft_strcmp(arg, "--") == 0)
	{
		last = 1;
		return (1);
	}
	if (ft_strchr(arg, '=') && ft_strchr(arg, '=') != arg)
	{
		last = 1;
		return (1);
	}
	if (!last && arg[0] == '-')
		return (1);
	if (!last && ft_strcmp(arg, "-u") == 0)
		return (1);
	return (0);
}

static void		decompose_argument(t_shell *shell, char **sp, t_command *c,
					int i)
{
	int			j;
	t_command	*add_here;

	add_here = c;
	if (what_limit(sp[0]) == '(')
		c->type = C_SUBSHELL;
	while (sp[i])
	{
		j = read_aggregation(shell, c, sp, i);
		if (j > 0)
			i += j - 1;
		else
		{
			sp[i] = unprotect(sp[i]);
			if ((c->path && ft_strcmp(c->path, "env") == 0) && add_here == c &&
				!is_env_arg(c, sp[i]))
			{
				c->env = secure_alloc(sizeof(t_command));
				add_here = c->env;
			}
			append_command_name(shell, add_here, sp[i]);
		}
		i++;
	}
	is_env_arg(NULL, NULL);
}

void			del_strsplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_strdel(&split[i]);
		i++;
	}
	ft_memdel((void**)&split);
}

void			decompose_command(t_shell *shell, char *line, t_command *c)
{
	char		**split;

	if (line == NULL || ft_strlen(line) == 0)
		return ;
	split = ft_strsplit(line, ' ');
	split = replace_all_arg(split, shell, c);
	if (split[0] == NULL || c->type == C_ERROR)
	{
		del_strsplit(split);
		return ;
	}
	decompose_argument(shell, split, c, 0);
	del_strsplit(split);
}
