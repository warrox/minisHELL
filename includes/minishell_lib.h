/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:37:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/24 13:11:54 by whamdi           ###   ########.fr       */
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
	int signal;
}t_signal;

typedef struct s_list_arg
{
	struct s_list_arg	*next;
	struct s_list_arg	*prev;
	char				**key_and_val;
	char				**cmd_and_arg;
	char				*input_splited;
	char				*result;
	int					redir_sign;
	int					*array_sign;

}						t_list_arg;

typedef struct s_data
{
	t_list_arg			*lst;
	t_list_arg			*tokenizer;
	t_list_arg			*sign_to_exe;
	t_prompt			*prompt;
	t_signal			*signal;
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
void	cmd_env(t_data *data, char *input);
void	pwd_cmd(t_data *data, char *input);
void					msg_error_handler(int *signal, t_data *data);
void cutting_input(t_data *data, char *input);
void	print_lst_token(t_list_arg *lst);
int check_quote(char *input, int i,t_data *data);
t_data *init_signal(t_data *data);
int checker_err_pipe(char *input,t_data *data);
int check_pipe(char *input, int i,t_data *data);
void  sort_sign(t_list_arg *tmp);
void parse_cmd_arg(t_data *data);
void	print_lst_cmdarg(t_list_arg *lst);
char	**split_tokenizer(char const *s, char c);

#endif
