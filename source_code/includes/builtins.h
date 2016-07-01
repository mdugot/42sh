/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 11:15:15 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/07 15:37:17 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "sh42.h"

void	do_echo(t_command *cmd, int fd_out, int fd_error);
void	set_env(t_command *c, t_shell *sh, int out, int err);
void	unset_env(t_command *c, t_shell *sh, int out, int err);
void	history(t_shell *sh, t_command *cmd, int o, int e);

#endif
