/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:37:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/07 15:41:57 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LIB_H
# define MINISHELL_LIB_H

# include "define.h"
# include "ft_printf.h"
# include "libft.h"
# include <readline/readline.h>
# include <stdio.h>

/*all structures*/

typedef struct s_prompt
{
	char				*usr_name;
	char				*usr_pwd;
	char				*usr_build_one;
	char				*usr_prompt;
}						t_prompt;

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
	t_prompt			*cstm_prompt;

}						t_data;

void					print_lst(t_list_arg *lst);
void					parser_list_init(t_data *data, char **envp);
t_list_arg				*ft_lst_arg_new(t_list_arg *new, char *content);
void					ft_lstadd_arg_back(t_list_arg **lst, t_list_arg *new);
t_list_arg				*ft_lst_arg_last(t_list_arg *lst);
void					ft_lst_arg_delone(t_list_arg *lst);
void					ft_lst_arg_clear(t_list_arg **lst);
void					parser_list_init(t_data *data, char **envp);
int						display_prompt(t_prompt *prompt, char **envp, t_data *data);
void					free_prompt(t_prompt *prompt);
char	*parser(char *input, t_data *data);
#endif
