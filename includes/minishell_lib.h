/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:37:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/04 17:16:53 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LIB_H
# define MINISHELL_LIB_H

/*all includes*/

# include "libft.h"
# include "ft_printf.h"
# include "define.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

/*all structures*/

typedef struct s_list_arg
{
	struct s_list_arg *next;
	struct s_list_arg *prev;
	char **key_and_val;// keyname ex : ls
	char *val; // value of the keyname - obsolette
	char *opt; // option ex -a
	//char *arg; to delete	
}			t_list_arg;

typedef struct s_data
{
	t_list_arg *lst;
} t_data;

void print_lst(t_list_arg *lst);
void parser_list_init(t_data *data, char **envp);
t_list_arg	*ft_lst_arg_new(t_list_arg *new,char *content);
void	ft_lstadd_arg_back(t_list_arg **lst, t_list_arg *new);
t_list_arg	*ft_lst_arg_last(t_list_arg *lst);
void    ft_lst_arg_delone(t_list_arg *lst);
void    ft_lst_arg_clear(t_list_arg **lst);
void parser_list_init(t_data *data, char **envp);
#endif
