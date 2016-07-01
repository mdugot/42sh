/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:17:58 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/16 17:16:40 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toolkit.h"
#include "libft.h"
#include <unistd.h>
#include "sh21.h"

int		t_putchar(int c)
{
	static t_term *term = NULL;

	if (!term)
		term = return_term(NULL);
	if (term)
		write(term->fd, &c, 1);
	return (1);
}

t_term	*return_term(t_term *term)
{
	static t_term *term_ptr = NULL;

	if (term)
		term_ptr = term;
	return (term_ptr);
}

char	*cur_pos_char_insert(t_shprop *shell, int c)
{
	char	*new;
	int		i;
	size_t	input_size;

	input_size = 0;
	if (shell->input)
		input_size = ft_strlen(shell->input);
	new = ft_strnew(input_size + 2);
	i = 0;
	while (i < shell->curs_pos)
	{
		new[i] = shell->input[i];
		i++;
	}
	new[i] = (char)c;
	while (++i <= (int)input_size)
		new[i] = shell->input[i - 1];
	if (shell->input)
		free(shell->input);
	shell->input = new;
	return (new);
}

char	*cur_pos_char_delete(t_shprop *shell)
{
	char	*new;
	int		i;
	size_t	input_size;

	input_size = 0;
	new = NULL;
	if (shell->input)
		input_size = ft_strlen(shell->input);
	if (input_size > 1)
	{
		new = ft_strnew(input_size);
		i = 0;
		while (i < shell->curs_pos)
		{
			new[i] = shell->input[i];
			i++;
		}
		while (++i <= (int)input_size)
			new[i - 1] = shell->input[i];
	}
	if (shell->input)
		free(shell->input);
	shell->input = new;
	return (new);
}

int		get_tab_index(char *line, int index)
{
	int count;

	count = -1;
	if (index < 0)
		return (0);
	while (index >= 0)
	{
		if (line[index] == '\t')
			count++;
		index--;
	}
	return (count);
}
