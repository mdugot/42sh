/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 11:31:14 by udelorme          #+#    #+#             */
/*   Updated: 2016/06/30 12:00:39 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# define DFT_TERM "xterm-256color"
# define DFT_PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

# define T_PRINT(x) 			tputs(x, term->fd, t_putchar)
# define T_GOTO(x, y) 			T_PRINT(tgoto(T_GET_MODE("cm"), x, y))
# define T_GET_MODE(x) 			tgetstr(x, NULL)
# define T_SETMODE(x) 			ft_putstr_fd(T_GET_MODE(x), term->fd)
# define T_SETDFT_MODE 			T_SETMODE("me")
# define IS_COMMAND_START(x)	(((x) == '|') || ((x) == ';') || ((x) == '&'))

# define DOWN_ARROW		4348699
# define UP_ARROW		4283163
# define LEFT_ARROW		4479771
# define RIGHT_ARROW	4414235
# define HOME_KEY		4741915
# define END_KEY		4610843
# define RETURN_KEY		10
# define BACKSPACE_KEY	127
# define ESC_KEY		27

# define QUOTES			0
# define DQUOTES		1
# define BQUOTES		2
# define PARENTH		3
# define ACC			4

# include "term.h"
# include <stdlib.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef struct			s_item
{
	char				*item_name;
	int					select;
	int					last;
	int					ind;
	struct s_item		*next;
	struct s_item		*prev;
}						t_item;

typedef struct			s_hist
{
	char				*line;
	int					stored;
	struct s_hist		*next;
	struct s_hist		*prev;
}						t_hist;

typedef struct			s_term
{
	char				*term_name;
	struct winsize		ws;
	struct termios		term;
	struct termios		term_bak;
	struct sigaction	new_sigs;
	int					fd;
}						t_term;

typedef struct			s_shprop
{
	t_term				*term;
	t_hist				*hist;
	int					hist_fd;
	int					hist_trunc;
	char				*hist_dir;
	char				*prompt;
	char				**env;
	char				*input;
	int					curs_pos;
	size_t				input_len;
	size_t				prompt_len;
	int					size_changed;
	void				*sh_ptr;
}						t_shprop;

/*
** Shell functions
*/

t_shprop				*init_shell(char **env);
int						init_termios(t_term *term, char **env);
int						rst_termios(t_term *term);
int						reinit_termios(t_term *term);
t_term					*return_term(t_term *term);
void					free_shell_input(t_shprop *shell);
void					aff_prompt(t_shprop *shell);
void					parse_line(t_shprop *shell);
int						check_complete_line(char *line);

char					*select_to_replace(char *str, int i);

int						handle_command(t_shprop *shell);
void					rpl_homedir_tild(char **str, char **env);
int						file_x_access(char *path);

void					replace_wildcards(t_shprop *shell);

/*
** Key functions
*/

void					add_char_input(t_shprop *shell, int key);
int						handle_key(t_shprop *shell, int key);
int						handle_edit_keys(t_shprop *shell, int key);
void					key_move_right(t_shprop *shell);
void					key_move_left(t_shprop *shell);
void					key_delete_char(t_shprop *shell);
void					key_act_return(t_shprop *shell);
void					key_move_home(t_shprop *shell);
void					key_move_end(t_shprop *shell);
void					key_move_next_word(t_shprop *shell);
void					key_move_last_word(t_shprop *shell);
void					key_move_line_up(t_shprop *shell);
void					key_move_line_down(t_shprop *shell);
void					key_move_up_history(t_shprop *shell);
void					key_move_down_history(t_shprop *shell);
void					update_hist_delete(t_shprop *shell);
int						key_tab_search(t_shprop *shell);
int						goto_next_line(t_shprop *shell);
int						goto_end_of_line(t_shprop *shell);
void					fill_lines(t_shprop *shell);
void					print_line_on_shell(t_shprop *shell, char *line);
void					insert_line_on_shell(t_shprop *shell, const char *line);
void					act_delete_line(t_shprop *shell);
void					fill_lines_delete(t_shprop *shell);
void					key_delete_right(t_shprop *shell);
void					sc_clear_screen(t_shprop *shell);

/*
** Fill functions
*/

int						complete_by_glob(t_shprop *shell, char *exp);
int						search_in_dir(t_shprop *shell, char *chr);
void					t_item_push(t_item **items, t_item *new);
void					free_cur_item(t_item *cur);
void					link_loop(t_item *first);
t_item					*t_item_new(char *name);

/*
**int				item_delete(t_all *global, t_item *cur_item);
*/

void					file_move_index_up(t_item *index);
void					file_move_index_down(t_item *index);
int						interrupt(int n);

#endif
