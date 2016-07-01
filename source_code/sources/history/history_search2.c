/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 09:55:36 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/29 22:21:08 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "sh42.h"
#include "libft.h"
#include "history.h"

int			handle_errors_excp(char *err_str, int err_code)
{
	char	*tmp;

	tmp = NULL;
	ft_putstr_fd("42sh: ", 2);
	if (err_code == 1)
		ft_putendl_fd("Syntax error near unexpected token \'newline\'", 2);
	else if (err_code == 2)
	{
		tmp = ft_strdup(err_str);
		tmp = unprotect(tmp);
		ft_putstr_fd(tmp, 2);
		ft_putendl_fd(": event not found", 2);
		ft_strdel(&tmp);
	}
	return (0);
}

/*
** mode == 1 --> search with strnstr
** mode == 2 --> search with strstr
** other --> don't search and return NULL
*/

char		*search_first_occurence_hist(t_hist *hist, char *chr, int mode)
{
	size_t	chr_len;

	if (hist)
	{
		hist = hist->next;
		if (chr)
		{
			chr_len = ft_strlen(chr);
			while (hist)
			{
				if (mode == 1)
				{
					if (ft_strnstr(hist->line, chr, chr_len))
						return (hist->line);
				}
				else if (mode == 2)
				{
					if (ft_strstr(hist->line, chr))
						return (hist->line);
				}
				hist = hist->next;
			}
		}
	}
	return (NULL);
}

char		*get_hist_index(t_hist *hist, char *search)
{
	int		decimal;
	char	*line;

	decimal = ft_atoi(search);
	line = NULL;
	if (decimal < 0)
	{
		while (hist && ++decimal <= 0)
			hist = hist->next;
		if (hist)
			line = hist->line;
	}
	else if (decimal > 0)
	{
		goto_begin_hist(&hist);
		while (hist && --decimal >= 1)
			hist = hist->prev;
		if (hist)
			line = hist->line;
	}
	return (line);
}

static char	*return_first_hist_match(t_hist *hist, char *chr,
			char *match, int err_code)
{
	char	*tmp;
	char	*ptr;

	tmp = ft_strdup(chr);
	ptr = tmp;
	tmp++;
	if (ft_strlen(tmp))
	{
		match = search_first_occurence_hist(hist, tmp, 1);
		err_code = 2;
		if (tmp && *tmp == '!' && hist->next)
			match = hist->next->line;
		else if (tmp && *tmp == '?' && hist->next)
		{
			del_all_char(tmp, '?');
			match = search_first_occurence_hist(hist, tmp, 2);
		}
		else if (ft_atoi(tmp))
			match = get_hist_index(hist, tmp);
	}
	else
		match = S_EXC_P;
	error_match(match, chr, err_code);
	free(ptr);
	return (match);
}

char		*hist_replaces(t_hist *hist, char *chr)
{
	char	*to_replace;

	to_replace = NULL;
	if (hist && hist->next)
	{
		to_replace = return_first_hist_match(hist, chr, NULL, 0);
		if (to_replace)
			return (ft_strdup(to_replace));
	}
	else
		handle_errors_excp(chr, 2);
	return (NULL);
}
