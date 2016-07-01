/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:10:07 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/29 22:21:08 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "sh42.h"
#include "libft.h"
#include "history.h"

char		*select_to_replace(char *str, int i)
{
	size_t len_cut;

	len_cut = 1;
	i++;
	if (str[i] == '!')
		return (ft_strsub(str, i - 1, 2));
	else if (str[i] == '?')
	{
		while (str[i + len_cut] && str[i + len_cut] != '?')
			len_cut++;
		return (ft_strsub(str, i - 1, len_cut + 2));
	}
	while (str[i + len_cut] && ft_isalnum(str[i + len_cut]))
		len_cut++;
	return (ft_strsub(str, i - 1, len_cut + 1));
}

/*
** if mode == 1 the function will protect from '?' and '!'
** if mode == 2 the function will unprotect from '?' and '!'
** any else mode will do nothing
*/

char		*secure_history_returns(char **str, int mode)
{
	if (mode == 1)
	{
		*str = ft_replace(*str, "!", S_EXC_P);
		*str = ft_replace(*str, "?", S_INT_P);
	}
	else if (mode == 2)
	{
		*str = ft_replace(*str, S_EXC_P, "!");
		*str = ft_replace(*str, S_INT_P, "?");
	}
	return (*str);
}

static void	replace_by_match(t_shprop *shell, char *to_replace, char **by)
{
	char	*tmp;

	secure_history_returns(by, 1);
	tmp = ft_replace(ft_strdup(shell->input), to_replace, *by);
	if (!tmp)
		return ;
	if (*tmp)
	{
		free(shell->input);
		shell->input = tmp;
	}
	ft_strdel(by);
	ft_strdel(&to_replace);
	shell->curs_pos = -1;
}

static void	search_in_hist2(t_shprop *shell, int modify)
{
	if (shell->input && modify)
		shell->input = secure_history_returns(&(shell)->input, 2);
	shell->input = unprotect(shell->input);
	if (shell->input && modify)
		ft_putendl_fd(shell->input, shell->term->fd);
}

int			search_in_hist(t_shprop *shell)
{
	char	*to_replace;
	char	*by;
	int		modify;

	shell->curs_pos = -1;
	modify = 0;
	if (!check_line(&(shell)->input))
		return (0);
	shell->input = protect_editor(shell->input);
	while (shell->input && shell->input[++(shell)->curs_pos])
	{
		if (shell->input[shell->curs_pos] == '!')
		{
			modify = 1;
			to_replace = select_to_replace(shell->input, shell->curs_pos);
			by = hist_replaces(shell->hist, to_replace);
			if (by)
				replace_by_match(shell, to_replace, &by);
			else
				return (no_match_free(&to_replace));
			shell->curs_pos = -1;
		}
	}
	search_in_hist2(shell, modify);
	return (1);
}
