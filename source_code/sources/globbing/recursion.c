/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 14:33:31 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/21 13:59:03 by rorousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static void		init(char ***files, int *i, char *temp[3], char *str)
{
	*i = 0;
	temp[0] = ft_strdup(str);
	temp[2] = create_save(temp[0]);
	*files = (char**)malloc(2 * sizeof(char*));
	files[0][0] = ft_strdup(str);
	files[0][1] = NULL;
}

static char		**glob_recursion_suite(char *str, char **files, char *temp[3])
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	while (i > 0 && str[i] != '/')
		i--;
	if (str[i] == '/')
		files[0][i] = '\0';
	else
	{
		files[0][0] = '.';
		files[0][1] = '\0';
	}
	i = 0;
	if (detect_double(str) == 0)
	{
		free(temp[0]);
		free(temp[2]);
		return (NULL);
	}
	return (launch(temp[0]));
}

static void		glob_recursion_boucle(char ***res, char ***files, char *temp[3])
{
	while (res[0][0] != NULL)
	{
		*files = add_double_char(*res, *files);
		temp[1] = ft_strjoin(temp[0], "/");
		free(temp[0]);
		temp[0] = ft_insert(temp[1]);
		free(temp[1]);
		*res = launch(temp[0]);
	}
	free_double_char(*res);
	free(temp[0]);
}

char			**glob_recursion(char *str)
{
	char	**files;
	char	**res;
	int		i;
	char	*temp[3];

	init(&files, &i, temp, str);
	if ((res = glob_recursion_suite(str, files, temp)) == NULL)
		return (NULL);
	glob_recursion_boucle(&res, &files, temp);
	if (files != NULL)
		recursion_recollage(files, temp[2]);
	while (files != NULL && files[i] != NULL)
	{
		res = ft_glob(files[i]);
		files = add_double_char(res, files);
		i++;
	}
	if (files != NULL)
		files = destroy_empty(files);
	return (files);
}
