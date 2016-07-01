/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_arg_subshell_globbing.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 08:52:48 by mressier          #+#    #+#             */
/*   Updated: 2016/06/28 15:59:31 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void			no_match_error(char **split, char *argv, t_command *c)
{
	char		*tmp;

	if (*split == NULL)
	{
		tmp = unprotect(ft_strdup(argv));
		command_error(c, "No matches", tmp);
		ft_strdel(&tmp);
	}
}

static char			**get_argv_split(char *argv, t_command *c, int *recul)
{
	char		**split;

	split = ft_glob(argv);
	no_match_error(split, argv, c);
	if (ft_strsplit_size(split) < 1)
		*recul = 1;
	return (split);
}

char				**replace_arg_by_globbing(char **argv, t_command *c)
{
	int		i;
	char	**split;
	int		recul;

	i = 0;
	recul = 0;
	while (argv[i])
	{
		del_all_char(argv[i], '"');
		del_all_char(argv[i], '\'');
		if (commun_char(argv[i], GLOB))
		{
			split = get_argv_split(argv[i], c, &recul);
			argv = replace_arg_by_split(argv, argv[i], split);
			if (recul == 1)
			{
				recul = 0;
				i--;
			}
		}
		i++;
	}
	return (argv);
}

char				**replace_arg_by_subshell(char **argv, t_shell *sh)
{
	int		i;
	int		recul;
	char	**split;

	i = 0;
	recul = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '`'))
		{
			del_all_char(argv[i], '"');
			del_all_char(argv[i], '\'');
			split = split_subshell(ft_strdup(argv[i]), sh, NULL, NULL);
			if (ft_strsplit_size(split) < 1)
				recul = 1;
			argv = replace_arg_by_split(argv, argv[i], split);
			if (recul == 1)
			{
				recul = 0;
				i--;
			}
		}
		i++;
	}
	return (argv);
}
