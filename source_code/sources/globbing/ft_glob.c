/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 14:25:09 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/29 15:42:40 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

char	**ft_glob(char *str)
{
	char	**ret;

	if (detect_double(str) > 0)
	{
		if (ft_strcmp(str, "**/") == 0)
			ret = glob_recursion("**/*/");
		else
			ret = glob_recursion(str);
	}
	else
		ret = launch(str);
	return (ret);
}
