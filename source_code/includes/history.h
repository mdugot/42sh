/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 15:09:02 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/29 22:27:40 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "sh42.h"

int			option_r(t_command *cmd, char *filename);
int			option_a(t_hist *hist, char *filename);
void		option_n(t_command *cmd, char *filename);
int			option_w(t_hist *hist, char *filename);
void		option_p(t_cmd_param *params, int len_params, int out_fd);
void		option_s(t_cmd_param *params, t_hist *hist, int len_params);
void		option_c(t_shprop *shell);

t_hist		*t_hist_new(char *line, int stored);
void		t_hist_push(t_hist **first, t_hist *new);
int			get_history(t_shprop *shell, int fd);
void		store_hist_line(char *line, int fd);
void		append_hist(t_shprop *shell);
int			hist_update(t_shprop *shell, int fd);
void		goto_end_list(t_shprop *shell);
int			goto_begin_hist(t_hist **hist);
int			goto_end_hist(t_hist **hist);
int			hist_delete_current_item(t_hist **hist);
void		file_hist_append(t_hist *hist, int fd);
void		store_hist_line(char *line, int fd);
int			search_in_hist(t_shprop *shell);
void		print_history_line(t_hist *hist, int i, int padding, int out_fd);

int			clear_history(t_hist **hist);
char		*hist_replaces(t_hist *hist, char *chr);
void		free_history(t_hist *hist);
int			history_errors(int err_code, char *str_err, int err_fd);
void		print_history(t_hist *hist, int last_n, int out_fd);
int			check_anrw(t_cmd_param *params);
int			handle_anrw(t_command *cmd, t_hist *hist
				, t_cmd_param *params, char *hist_path);
int			print_n_last_lines(t_command *cmd
				, t_cmd_param *param, int err_fd, int out_fd);
int			handle_ps(t_hist *hist, t_cmd_param *params, int out_fd);
int			handle_errors_excp(char *err_str, int err_code);
int			check_line(char **line);
void		error_match(char *match, char *chr, int err_code);
int			no_match_free(char **to_replace);

#endif
