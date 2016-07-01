/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 12:09:25 by rsibiet           #+#    #+#             */
/*   Updated: 2016/06/30 14:26:08 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

# define CMD struct s_command
# define SH struct s_shell
# define CLOSED 256

# include <pwd.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "sh21.h"
# include "globbing.h"

# define S_EXC_P "\033@33"
# define S_INT_P "\033@63"
# define SYNTAX "!$\\`;|&*?[]{}()'\"<>- \n\t"
# define GLOB "*?[]{}"

/*
** int fd_logfile; debug
*/

typedef struct			s_command_pipe
{
	int					error[2];
	int					out[2];
	int					in[2];
	int					send_to[2];
}						t_command_pipe;

typedef enum			e_fd_type
{
	FDT_NULL = 0,
	FDT_IN,
	FDT_OUT,
	FDT_IN_OUT,
	FDT_APPEND_OUT,
	FDT_EOF_IN,
	FDT_DEFAULT
}						t_fd_type;

typedef enum			e_dir_type
{
	DT_IN = 0,
	DT_OUT,
	DT_ERR,
	DT_NULL
}						t_dir_type;

typedef enum			e_next_type
{
	NEXT_DEFAULT = 0,
	NEXT_AND, NEXT_OR,
	NEXT_INTERRUPTION
}						t_next_type;

typedef enum			e_status_type
{
	ST_NORMAL = 1,
	ST_SIGNAL,
	ST_STOP
}						t_status_type;

typedef enum			e_type_command
{
	C_VOID = 0,
	C_BUILTIN,
	C_BIN,
	C_ERROR,
	C_SUBSHELL
}						t_type_command;

typedef struct			s_in
{
	int					id;
	int					fd;
	char				*eof;
	char				*buff;
}						t_in;

typedef struct			s_out
{
	int					id;
	int					fd;
	int					file_to_close;
	int					append;
}						t_out;

typedef struct			s_command
{
	int					first;
	char				*line;
	char				**argv;
	int					argc;
	char				*path;
	char				*error_message;
	char				*error_name;
	t_type_command		type;
	CMD					*env;
	t_next_type			next_type;
	CMD					*next;
	CMD					*pipe;
	CMD					*pipe_previous;
	int					fd_in[257];
	int					fd_out[257];
	int					fd_error[257];
	t_list				*list_out;
	t_list				*list_in;
	SH					*shell;
}						t_command;

typedef struct			s_fd
{
	int					fd;
	int					write_right;
	int					read_right;
	t_fd_type			type;
	int					occupy;
}						t_fd;

typedef struct			s_fd_tmp
{
	int					fd;
	char				*name;
}						t_fd_tmp;

typedef struct			s_shell
{
	t_shprop			*edit;
	char				*cwd;
	char				**env;
	char				**local;
	int					save_out;
	int					save_in;
	int					save_error;
	int					last_status;
	int					last_status_type;
	int					inside_status;
	pid_t				to_kill;
}						t_shell;

typedef struct			s_cmd_param
{
	char				*param;
	struct s_cmd_param	*args;
	int					is_option;
	struct s_cmd_param	*next;
	struct s_cmd_param	*prev;
}						t_cmd_param;

/*
**  	------------------------------------------------------
**  	|					OUTSIDE FOLDERS		         	 |
**  	------------------------------------------------------
*/

/*
** new_shell.c
*/
t_shell					*new_shell(char **env, t_shprop *edit);

/*
** debug.c
*/
void					print_command(t_command *c);

/*
** decompose_codition.c
*/
t_command				*cut_and(char *line);

/*
** number.c
*/
int						read_positive_number(char **str, int modulo);
int						is_positive_number(const char *str);
int						len_number(const char *str);

/*
** str_subshell.c
*/
char					*str_subshell(char *line, t_shell *shell);

/*
** subshell.c
*/
void					subshell(t_shell *shell, t_command *cmd);
void					do_subshell(t_shell *shell, char *str, int b_exit);

/*
** protect_citation_backslash.c
*/
char					*protect_citation(char *str);
char					*protect_backslash(char *line);
char					*protect_backslash_with_backslash(char *line);

/*
** limit_protect.c
*/
char					what_limit(char *line);
char					*chop_limit(char *line);

/*
** protect_.c
*/
char					*protect_all(char *line);
char					*protect(char *line);
char					*protect_editor(char *line);
char					*unprotect(char *line);

/*
** handle_signal.c
*/
void					signal_handler(int sig);

/*
** signal.c
*/
int						interrupt(int n);
void					rst_signals(t_term *term);
t_shell					*shell_adress(t_shell *ad);
void					change_signal_mode(t_term *term, int mode);

/*
** replace_all_arg.c
*/
char					**replace_all_arg(char **split, t_shell *sh, CMD *c);

/*
** replace_arg_subshell_globbing.c
*/
char					**replace_arg_by_subshell(char **argv, t_shell *sh);
char					**replace_arg_by_globbing(char **argv, t_command *c);

/*
** replace_arg_by_split.c
*/
char					**replace_arg_by_split(char **old, char *arg,
							char **split);

/*
** split_subshell.c
*/
char					**split_subshell(char *arg, t_shell *sh, char *tmp,
							char *tmp2);

/*
**  	------------------------------------------------------
**  	|						SYNTAX		         	     |
**  	------------------------------------------------------
*/

/*
** is_syntax.c
*/
int						is_syntax(char **str);

/*
** cut_on_syntax.c
*/
t_command				*cut_semicolon(t_shell *shell, char *line);
t_command				*cut_pipe(char *line);

/*
** syntax_error.c
*/
int						parenthesis_error(char **str, int *r);
int						backquote_error(char **str, int *r);
int						syntax_error(char *line);

/*
** quote_error.c
*/
int						quote_error(char **str, int *r, int end);

/*
** pass_syntax.c
*/
void					pass_backquote(char **str, int *r);
int						pass_redirection(char **str);

/*
** go_next_syntax.c
*/
int						go_next_syntax(char **str, char end);

/*
** find_limit.c
*/
void					find_limit(char c, char *begin, char *end);

/*
** syntax_redirection
*/
char					*correct_syntax_redirection(char *line);
int						pass_citation(char *line, int *i);

/*
** syntax_parenthesis
*/
char					*correct_parenthesis(char *line);

/*
** read_aggregation.c
*/
int						read_aggregation(t_shell *sh, CMD *c, char **s, int i);

/*
** read_redirection.c
*/
int						read_redirection(t_shell *sh, CMD *c, char **s, int i);
char					*r_argument(char **split, int i, char *name, int *r);

/*
** read_fd.c
*/
int						read_fd(t_shell *sh, t_command *c, char **s, int i);

/*
**  	------------------------------------------------------
**  	|						EXEC		         	     |
**  	------------------------------------------------------
*/

/*
** execute_and_distrib.c
*/
pid_t					execute_and_distrib(t_shell *sh, t_command *c);

/*
** distrib_and_send.c
*/
pid_t					distrib_and_send(t_shell *sh, CMD *c, int o, int e);

/*
** receipt_and_execute.c
*/
pid_t					receipt_and_execute(t_shell *sh, CMD *c, int r_fd);

/*
** execute_extern.c
*/
int						execute_extern(t_shell *sh, CMD *c, int fd_out,
							int fd_error);

/*
** execute_outils.c
*/
void					exe_prepa(t_shell *sh, CMD *c, int o[2], int e[2]);
int						execute_all(SH *sh, CMD *c, int o[2][2], int p[2][2]);
int						is_extern_builtin(t_command *c);

/*
** write_output_shell.c
*/
void					write_output_shell(int fd_out, int fd_error);

/*
**  	------------------------------------------------------
**  	|						BUILTINS		         	 |
**  	------------------------------------------------------
*/

/*
** cd_error.c
*/
int						cd_error(int err, char *path);

/*
** cd_check_params.c
*/
int						check_params(t_cmd_param *params, t_shell *shell,
							int *fds, char **path);

/*
** get_home_or_pwd_var.c
*/
char					*get_home_var(char **env, int err);
char					*get_oldpwd_var(char **env, int err);

/*
** change_current_directory.c
*/
int						change_current_directory(t_shell *shell,
							t_cmd_param *params, char *path, int *fds);

/*
** change_directory.c
*/
void					change_directory(CMD *c, t_shell *sh, int o, int e);

/*
** find_env.c
*/
char					*find_env(char **env, char *name);

/*
** forge_new_env.c
*/
int						forge_new_env(t_shell *shell, t_command *cmd);

/*
** is_builtin.c
*/
int						is_builtin(const char *str);

/*
** exec_builtin.c
*/
void					exec_builtin(t_shell *sh, CMD *c, int out, int err);

/*
**  	------------------------------------------------------
**  	|						TOOLS		         	     |
**  	------------------------------------------------------
*/

/*
** replace_tild.c
*/
char					*replace_tild(char **env, char *str);

/*
** status.c
*/
int						exit_status(int status, t_shell *sh);
void					change_status(t_shell *sh, int n);

/*
** utils.c
*/
int						quit(t_shell *shell, int n);
int						commun_char(char *s1, char *s2);
int						has_syntax_in(char *str);

/*
** is_limit_begin_end.c
*/
int						is_limit_begin(char *str, char *c, char *begin_str);
int						is_limit_end(char *str, char *ac, char begin);

/*
** replace_in_out
*/
char					*replace_in(char *str, char *del, char *put, char *s);
char					*replace_out(char *str, char *del, char *put, char *s);
char					*replace_begin(char *s, int *i, char *d, char *p);

/*
** update_inside.c
*/
int						update_inside(char *begin, char *str, int *i, char *s);

/*
** is_sequence.c
*/
int						is_escaped(const char *str, char *c);
int						is_in(char *str, char *c, char *s);
int						is_closed(char *str, char *s);

/*
** del_all_char.c
*/
void					del_all_char(char *line, char c);

/*
** reprint_all_lines.c
*/
void					reprint_all_line(t_shprop *shell);

/*
** reduce_path.c
*/
char					*reduce_path(char *path);

/*
** join_paths.c
*/
char					*join_paths(char *base_path, char *to_add);

/*
** delete_useless_exp.c
*/
char					*delete_useless_exp(char *path);

/*
**  	------------------------------------------------------
**  	|							EDIT	         	     |
**  	------------------------------------------------------
*/

/*
** match_chr.c
*/
int						match_chr(t_shprop *shell, char *path, char *chr);

/*
** completion.c
*/
t_item					*select_mode_search(t_shprop *sh, char *p, char *chr);
int						free_match_vars(t_item *items, char **comp, int ret);
char					*complete_name_type_file(char *path, t_item *item);

int						get_one_input(void);
int						get_input(t_shprop *shell,
							int (*handle)(t_shprop *, int));
int						get_eof_input(t_shprop *shell, char **line);
void					replace_and_print_completed(t_shprop *shell, char *new,
							size_t len, int video_mode);
t_item					*get_commands_items(char **env, char *chr);
t_item					*get_dir_items(char *path, char *chr);
int						is_valid_item(char *chr, char *item_name);
t_item					*t_item_place(t_item **first, t_item *new);
char					*get_next_command(t_shell *shell);
void					*secure_alloc(size_t size);
void					exit_error(char *str);
char					**env_copy(char **env);
void					append_command_name(t_shell *sh, t_command *c, char *s);
char					*bin_path(t_shell *sh, char **env, char *bin, int *pd);
int						command_error(t_command *c, char *message, char *name);
int						add_redirection_out(CMD *c, int id, char *f, int a);
int						add_redirection_in(CMD *c, int id, char *arg, int eof);
int						add_aggregation(t_command *c, t_dir_type t, char *fd);
int						temporary_fd(t_shell *sh, int n, char *eof, CMD *c);
void					execute(t_shell *s, t_command *c, t_next_type t);
void					pipe_in(t_list *list, t_command *c, int pi, int rf);
void					pipe_out(t_command *c, int po, int st);
void					pipe_error(t_command *c, int err, int send_to);
void					close_pipe(t_command_pipe *cpipe);
void					write_in(t_in *in, int destination);
int						write_out(char*buff, t_list *list, t_command *command);
int						write_error(char *buff, t_list *list, t_command *c);

/*
** void					init_signal(t_term *term);
*/

void					init_signal(t_term *term, int mode);
void					pipe_from_eof(int fd, char *eof);
void					pipe_from_file(int fd, int file);
void					replace_whitespace(char *line);
char					*print_prompt(t_shell *shell, size_t *len);
void					exec_error(t_command *command, int err);
int						pipe_error_eof(t_in *in, char *eof, t_command *c);
int						pipe_error_file(t_in *in, char *name, t_command *c);
void					drain_pipe(int fd);
void					decompose_command(t_shell *shell, char *line, CMD *c);
int						is_default_in(int *fd, t_list *list, CMD *c);
int						is_default_out(int *fd, t_list *list, CMD *c);
int						is_directory(char *file);
int						is_correct_varname(char *name, int err, char *cmd);
char					**env_add(char **env, char *var, char *content);
void					print_env(char **env, int out);
char					**env_delete(char **env, char *to_delete);
char					*edit(t_shell *shell);
void					free_shell(t_shell *sh);
void					free_shprop(t_shprop **shprop);
void					free_command(t_command *c);
void					env_free(char **env);
char					**env_arg(char *arg, char **env);
char					**env_replace(char **env, char *var, char *content);
int						env_cmp(char *var_con, char *var);
char					**update_shlvl(char **env);

/*
**char					*add_env_prefix(char **env, char *s, char *v, int td);
*/

t_command				*last_command(t_command *c);
int						not_closed_double(char *str, char begin, char end);
int						not_closed_simple(char *str, char c);
char					*unprotect_citation(char *str);
void					init_command(t_shell *sh, t_command *cmd, char *name);
void					do_read(t_command *cmd, t_shell *sh, int out, int err);
void					del_all_char(char *line, char c);
char					*unprotect_backslash(char *line);
void					clean_exit(t_term *term, int key_code, t_shell *sh);
void					set_local(t_command *c, t_shell *sh, int out, int err);
void					unset_local(t_command *c, t_shell *sh, int o, int e);
void					do_export(t_command *c, t_shell *sh, int out, int err);
char					*replace_variable(char *line, t_shell *sh);
int						parse_error(t_command *cmd);
void					add_parse_error(t_command *cmd);
int						is_redirection(char **str);

/*
** Parsing arguments builtins
*/

t_cmd_param				*parse_arguments(t_command *cmd, char *no_args,
							char *single_args);
int						find_existing_param(t_cmd_param **params, char *chr);
int						count_arguments(t_cmd_param *param);
int						count_params(t_cmd_param *param);
int						delete_item_by_id(t_hist *hist, t_cmd_param *param,
							int err_fd);
void					goto_begin_args(t_cmd_param **params);
void					free_options_list(t_cmd_param **parsed);
t_cmd_param				*cmd_param_new(char *param, int is_option);
int						is_option(char *arg);
int						find_and_add_options(t_cmd_param **params,
							char *options, char *no_arg, char *single_arg);
void					cmd_arg_push(t_cmd_param *current, t_cmd_param *new);
void					cmd_param_push(t_cmd_param **all, t_cmd_param *new);
void					handle_error_messages(t_shell *shell);
int						find_arg_type(char *arg, char *no_arg,
							char *single_arg);
int						find_existing_param(t_cmd_param **params, char *chr);

#endif
