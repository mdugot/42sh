/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorousse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 14:24:10 by rorousse          #+#    #+#             */
/*   Updated: 2016/06/29 22:00:05 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H

# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include "libft.h"

struct						s_list_glob
{
	char				*name;
	struct s_list_glob	*next;
	struct s_list_glob	*prec;
};

typedef struct s_list_glob	t_list_glob;

struct						s_dir_ext
{
	DIR					*mydir;
	struct dirent		*lecture;
	char				*save;
};

typedef struct s_dir_ext	t_dir_ext;

/*
** ACCOLADES_C
*/

char						**split_accolades(char *str);

/*
** ACCOLADES_2_C
*/

int							verif_accolades(char **listing);
int							get_size_accolade(char *accolade);

/*
** BRACKET_C
*/

char						*make_bracket(const char *str, int y);

/*
** COMPS_C
*/

int							glob_strncmp(char *s1, char *s2, size_t n);
char						*glob_strstr(char *s1, char *s2);

/*
** DIV_C
*/

int							ft_glob_strlen(char *str);
void						print_double_char(char **str);
char						**destroy_empty(char **str);
void						kill_star_in_brackets(char **str);

/*
** DOUBLE_CHAR_C
*/

void						free_double_char(char **str);
int							get_size_double_char(char **str);
char						**add_double_char(char **l1, char **l2);

/*
** ERROR_C
*/

int							check_error(char *str);

/*
** FT_GLOB_C
*/

char						**ft_glob(char *str);

/*
** FT_INSERT_C
*/

char						*ft_insert(char *str);

/*
** GLOBBING_C
*/

char						**globbing(char *str);

/*
** GLOB_CMP_C
*/

int							glob_cmp(char *wild, char *str);
int							meta_glob_cmp(char *wild, char *str);

/*
** LISTING_C
*/

int							size_list(t_list_glob *lst);
char						**conversion(t_list_glob **lst);
int							check_existence(t_list_glob *lst, char *str);
void						add_lst(t_list_glob **lst, char *name);

/*
** PROTECTION_C
*/

void						protec_glob_file(char *str);
void						protec_glob_str(char **str);
void						unprotect_glob(char *str);

/*
** LAUNCH_C
*/

char						**launch(char *str);

/*
** RECURSION_C
*/

int							detect_double(char *str);
char						**glob_recursion(char *str);

/*
** RECURSION_ANNEXE_C
*/

char						*create_save(char *str);
void						recursion_recollage(char **files, char *str);
int							detect_double(char *str);

/*
** GLOBBING_FREE_C
*/

int							free_and_quit(char *str);
char						**free_and_quit_null(char *str);

#endif
