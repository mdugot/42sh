/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 14:53:46 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/29 23:00:22 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

char			*get_host_and_user(void)
{
	char			host[255];
	char			*ret;
	pid_t			user;
	struct passwd	*user_infos;
	char			*tmp;

	user = geteuid();
	user_infos = NULL;
	ret = NULL;
	if (user != -1)
	{
		user_infos = getpwuid(user);
		if (gethostname(host, sizeof(host)) != -1)
		{
			tmp = ft_strsub(host, 0, ft_index_fmatch(host, '.'));
			ret = ft_strnew(ft_strlen(tmp) +
				ft_strlen(user_infos->pw_name) + 2);
			ft_strcat(ret, user_infos->pw_name);
			ft_strcat(ret, "@");
			ft_strcat(ret, tmp);
			free(tmp);
		}
	}
	return (ret);
}

static char		*get_home_tmp(char *tmp, int *len_home, t_shell *shell)
{
	char	*home;
	int		i;

	i = -1;
	home = find_env(shell->env, "HOME");
	if (home && *home && ft_strncmp(tmp, home, ft_strlen(home)) == 0)
	{
		*len_home = ft_strlen(home);
		while (++i < *len_home)
			tmp++;
	}
	return (tmp);
}

static char		*get_all_datas(int len_home, char *tmp,
					char *meta_infos, size_t *len)
{
	if (len_home)
	{
		*len += 1;
		if (meta_infos)
			tmp = ft_strf("#G%s #Y~%s#C%%#N ", meta_infos, tmp);
		else
			tmp = ft_strf("#M~%s#C%%#N ", tmp);
	}
	else
	{
		if (meta_infos)
			tmp = ft_strf("#G%s #Y%s#C%%#N ", meta_infos, tmp);
		else
			tmp = ft_strf("#M%s#C%%#N ", tmp);
	}
	return (tmp);
}

char			*print_prompt(t_shell *shell, size_t *len)
{
	char	*tmp;
	int		len_home;
	char	*meta_infos;

	*len = 2;
	len_home = 0;
	if (shell->cwd == NULL)
		return (ft_strf("#C%%#N "));
	tmp = shell->cwd;
	tmp = get_home_tmp(tmp, &len_home, shell);
	*len += ft_strlen(tmp);
	meta_infos = get_host_and_user();
	if (meta_infos)
		*len += ft_strlen(meta_infos) + 1;
	tmp = get_all_datas(len_home, tmp, meta_infos, len);
	if (meta_infos)
		ft_strdel(&meta_infos);
	return (tmp);
}
