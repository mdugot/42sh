# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomo-chan <tomo-chan@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 12:08:51 by mdugot            #+#    #+#              #
#    Updated: 2016/06/29 22:00:31 by mdugot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= 42sh
CC= gcc
CFLAGS= -Wall -Werror -Wextra -g3 #-fsanitize=address
SRC_NAME= main.c number.c command_decompose.c command_edit.c error.c \
		  decompose_utils.c debug.c fd_utils.c path.c \
		  redirection_utils.c aggregation_utils.c pipe.c \
		  pipe_utils.c signal.c prompt.c exec/execute_outils.c \
		  env_utils.c memory.c env_options.c decompose_condition.c \
		  memory_2.c history/options_hist.c history/history_util.c \
		  protect.c subshell.c split_subshell.c parse_error.c \
		  syntax/syntax_redirection.c syntax/syntax_parenthesis.c \
		  edit/completion.c edit/completion2.c edit/completion3.c \
		  edit/init_shell.c edit/key_moves.c \
		  edit/key_str_acts.c edit/input_actions.c edit/termios_func.c \
		  edit/parse_line.c edit/toolkit.c history/hist.c history/hist2.c \
		  edit/match_files.c history/options_hist2.c\
		  history/builtin_history.c history/builtin_history2.c \
		  history/builtin_history3.c edit/key_acts.c \
		  edit/key_history.c edit/key_moves_2.c edit/shortcuts.c \
		  argument_parsing.c argument_parsing2.c argument_parsing3.c \
		  argument_parsing4.c history/history_search.c \
		  history/history_search2.c history/history_search3.c \
		  globbing/accolades.c globbing/accolades_2.c globbing/bracket.c \
		  globbing/comps.c globbing/div.c globbing/double_char.c \
		  globbing/glob_cmp.c globbing/globbing.c globbing/listing.c \
		  globbing/launch.c globbing/ft_glob.c globbing/globbing_free.c\
		  globbing/recursion.c globbing/ft_insert.c signal_messages.c \
		  globbing/recursion_annexe.c globbing/error.c\
		  builtins/is_builtin.c builtins/echo.c builtins/local2.c\
		  builtins/change_directory.c builtins/find_env.c builtins/setenv.c \
		  builtins/unsetenv.c builtins/read.c builtins/local.c \
		  builtins/export.c syntax/is_syntax.c syntax/go_next_syntax.c \
		  syntax/cut_on_syntax.c syntax/syntax_error.c syntax/quote_error.c \
		  syntax/pass_syntax.c tools/replace_tild.c tools/status.c \
		  tools/is_directory.c tools/utils.c tools/is_limit_begin_end.c \
		  tools/replace_in_out.c tools/update_inside.c tools/is_sequence.c \
		  str_subshell.c syntax/read_aggregation.c syntax/read_redirection.c \
		  syntax/read_fd.c protect_citation_backslash.c limit_protect.c \
		  tools/del_all_char.c handle_signal.c tools/reprint_all_lines.c \
		  replace_all_arg.c replace_arg_subshell_globbing.c \
		  replace_arg_by_split.c exec/execute.c exec/execute_and_distrib.c \
		  exec/distrib_and_send.c exec/receipt_and_execute.c \
		  builtins/cd_error.c builtins/cd_check_params.c \
		  builtins/get_home_or_pwd_var.c tools/reduce_path.c tools/join_paths.c \
		  builtins/change_current_directory.c tools/delete_useless_exp.c \
		  exec/write_output_shell.c exec/execute_extern.c \
		  builtins/forge_new_env.c builtins/exec_builtin.c new_shell.c \
		  edit/match_chr.c

SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= libft.a
LIB_ID= ft
LIB_PATH= ./libft/
LIB_INC= ./libft/includes/
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))

.PHONY: all
all: $(NAME) end
	
end:
	@printf "\n$(NAME) successfully created\n"
	@printf "Run with \033[32m./$(NAME)\033[0m\n"

$(NAME): $(LIB) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) -L$(LIB_PATH) -I$(INC_PATH) -l$(LIB_ID) -ltermcap $(OBJ) 
	@printf "\033[2K[ \033[31mcompiling\033[0m ] $< \r"

$(LIB):
	@make re -C $(LIB_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/edit 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/history 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/globbing 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/builtins 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/syntax 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/tools 2> /dev/null || echo "" > /dev/null
	@mkdir $(OBJ_PATH)/exec 2> /dev/null || echo "" > /dev/null
	@$(CC) -I$(INC_PATH) -I$(LIB_INC) $(CFLAGS) -o $@ -c $<
	@printf " \033[2K[ \033[31mcompiling\033[0m ] $< \r"

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@printf "[ \033[36mdelete\033[0m ] objects from $(NAME)\n"
	@rm -rf $(OBJ_PATH)
	@make $@ -C $(LIB_PATH)

.PHONY: fclean
fclean: clean
	@printf "[ \033[36mdelete\033[0m ] $(NAME)\n"
	@rm -f $(NAME)
	@make $@ -C $(LIB_PATH)

.PHONY: re
re: fclean all
