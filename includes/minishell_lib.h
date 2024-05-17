/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:37:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/17 19:06:41 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LIB_H
# define MINISHELL_LIB_H

/*all includes*/

# include "define.h"
# include "ft_printf.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

/*all structures*/

typedef struct s_prompt
{
	char				*usr_name;
	char				*usr_pwd;
	char				*usr_build_one;
	char				*usr_build_two;
	char				*usr_prompt;
}						t_prompt;
typedef struct s_signal
{
	int					signal;
}						t_signal;

typedef struct s_list_arg
{
	struct s_list_arg	*next;
	struct s_list_arg	*prev;
	char				**key_and_val;
	char				*val;
	char				*opt;
}						t_list_arg;

typedef struct s_data
{
	t_list_arg			*lst;
	t_prompt			*prompt;
	t_signal			*signal;
	int					i;

}						t_data;

void					print_lst(t_list_arg *lst);
void					parser_list_init(t_data *data, char **envp);
t_list_arg				*ft_lst_arg_new(t_list_arg *new, char *content);
void					ft_lstadd_arg_back(t_list_arg **lst, t_list_arg *new);
t_list_arg				*ft_lst_arg_last(t_list_arg *lst);
void					ft_lst_arg_delone(t_list_arg *lst);
void					ft_lst_arg_clear(t_list_arg **lst);
void					parser_list_init(t_data *data, char **envp);
int						display_prompt(t_data *data);
void					free_prompt(t_data *data);
char					*parser(char *input, t_data *data);
t_data					*build_user_prompt(t_data *data);
t_data					*init_prompt(t_data *data);
void					cmd_env(t_data *data, char *input);
void					pwd_cmd(char *input);
void					cmd_export(t_data *data, char *input);
void					msg_error_handler(int *signal, t_data *data);
int						check_plus_egal(char *input);
void					concat_env_var(t_data *data, char *value, char *new);
void					export_case(t_data *data, t_list_arg *tmp, char **arg,
							char **split);
void					case_plus_egal(t_data *data, t_list_arg *tmp,
							char **arg, char *tmp_built);
void					set_value(t_data *data, char *value, char *new);
int						check_egals(char *input);
void					cmd_unset(t_data *data, char *input);
void					free_split(char **split);
void					check_export_cmd(char *input, t_data *data);
void					print_lst_export(t_list_arg *lst);
void					check_if_null(t_data *data, t_list_arg *tmp,
							char **split);
void					exec_export_case(t_data *data, t_list_arg *tmp,
							char **split, char **arg);
t_list_arg				*parse_key_and_val(t_list_arg *tmp);

#endif
