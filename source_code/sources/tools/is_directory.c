/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mressier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 14:11:22 by mressier          #+#    #+#             */
/*   Updated: 2016/06/27 14:11:23 by mressier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

int		is_directory(char *file)
{
	int			r;
	struct stat	s;

	if (stat(file, &s) == -1)
		return (0);
	r = S_ISDIR(s.st_mode);
	return (r);
}
