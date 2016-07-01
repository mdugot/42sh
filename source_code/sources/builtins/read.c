/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 14:40:52 by mdugot            #+#    #+#             */
/*   Updated: 2016/06/30 13:38:44 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*read_one_line(int treat_backslash, t_shell *sh)
{
	char	*line;
	char	*tmp;
	char	*tmp2;
	int		status;

	line = NULL;
	(void)sh;
	status = get_next_line(0, &line);
	while (line[ft_strlen(line) - 1] == '\\' && treat_backslash && status > 0)
	{
		line[ft_strlen(line) - 1] = '\0';
		tmp = line;
		status = get_next_line(0, &tmp2);
		line = ft_strjoin(tmp, tmp2);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	if (line[ft_strlen(line) - 1] == '\\' && treat_backslash)
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

char	**split_read_line_default(int treat_backslash, int max, t_shell *sh)
{
	int		i;
	char	**split;
	char	*line;

	line = read_one_line(treat_backslash, sh);
	i = 0;
	if (treat_backslash)
		line = protect_backslash(line);
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\n')
			line[i] = ' ';
		i++;
	}
	split = ft_strsplit_max(line, ' ', max);
	if (treat_backslash)
	{
		i = -1;
		while (split[++i])
			split[i] = unprotect(split[i]);
	}
	ft_strdel(&line);
	return (split);
}

void	add_all_variables(t_cmd_param *param, int treat_backslash, t_shell *sh)
{
	int		i;
	char	**split;
	int		number_var;
	int		split_size;

	number_var = count_params(param);
	split = split_read_line_default(treat_backslash, number_var, sh);
	split_size = ft_strsplit_size(split);
	param = param->args;
	i = 0;
	while (param)
	{
		if (i < split_size)
			sh->local = env_add(sh->local, param->param, split[i]);
		else
			sh->local = env_add(sh->local, param->param, "");
		i++;
		param = param->args;
	}
	ft_deltab(split, split_size);
}

void	do_read(t_command *cmd, t_shell *sh, int out, int err)
{
	int			treat_backslash;
	t_cmd_param *params;
	t_cmd_param *tmp;

	(void)out;
	if (cmd->argc <= 1)
		return ;
	treat_backslash = 1;
	params = parse_arguments(cmd, "r", "");
	if (ft_strcmp(params->param, "fail") == 0)
	{
		ft_printf_fd(err, "42sh: read: %s: invalid option\n",
			params->args->param);
		ft_printf_fd(err, "read: usage: read [-r] var ...\n");
		change_status(sh, 1);
		return ;
	}
	if (find_existing_param(&params, "r"))
		treat_backslash = 0;
	tmp = params;
	if (find_existing_param(&tmp, "other"))
		add_all_variables(tmp, treat_backslash, sh);
	goto_begin_args(&params);
	free_options_list(&params);
}
