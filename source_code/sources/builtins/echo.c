/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 11:13:48 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/27 17:46:29 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "libft.h"

char		*replace_first(char *str, char *del, char *put)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(&str[i], del, ft_strlen(del)) == 0)
		{
			str = replace_begin(str, &i, del, put);
			return (str);
		}
		i++;
	}
	return (str);
}

char		*echo_replace_value(char *str)
{
	char	*tmp;
	char	value[2];
	int		i;

	value[1] = 0;
	while ((tmp = ft_strstr(str, "\\0")))
	{
		tmp = ft_strdup(tmp);
		i = 1;
		while (i < 5 && tmp[i] >= '0' && tmp[i] <= '7')
			i++;
		tmp[i] = 0;
		value[0] = ft_atoi_base(&tmp[1], 8);
		str = replace_first(str, tmp, value);
		ft_strdel(&tmp);
	}
	return (str);
}

char		*echo_replace(char *str, int *nl)
{
	char	*result;
	int		i;

	i = -1;
	result = ft_strdup(str);
	result = echo_replace_value(result);
	result = ft_replace(result, "\\a", "\a");
	result = ft_replace(result, "\\b", "\b");
	result = ft_replace(result, "\\f", "\f");
	result = ft_replace(result, "\\n", "\n");
	result = ft_replace(result, "\\r", "\r");
	result = ft_replace(result, "\\t", "\t");
	result = ft_replace(result, "\\v", "\v");
	result = ft_replace(result, "\\\\", "\\");
	while (result[++i])
		if (result[i] == '\\' && result[i + 1] == 'c')
		{
			*nl = 0;
			result[i] = 0;
			break ;
		}
	return (result);
}

void		do_echo(t_command *cmd, int fd_out, int fd_error)
{
	int			i;
	char		*tmp;
	int			nl;

	(void)fd_error;
	i = 1;
	nl = 1;
	while (i < cmd->argc)
	{
		tmp = echo_replace(cmd->argv[i], &nl);
		ft_putstr_fd(tmp, fd_out);
		ft_strdel(&tmp);
		i++;
		if (i < cmd->argc)
			ft_putstr_fd(" ", fd_out);
	}
	if (nl)
		ft_putendl_fd("", fd_out);
	change_status(cmd->shell, 0);
}
