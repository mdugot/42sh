/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 11:22:29 by udelorme          #+#    #+#             */
/*   Updated: 2016/05/10 15:23:43 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLKIT_H
# define TOOLKIT_H

# include "sh21.h"

int		t_putchar(int c);
t_term	*return_term(t_term *term);
char	*cur_pos_char_insert(t_shprop *shell, int c);
char	*cur_pos_str_insert(t_shprop *shell, char *str);
char	*cur_pos_char_delete(t_shprop *shell);
int		get_tab_index(char *line, int index);

#endif
