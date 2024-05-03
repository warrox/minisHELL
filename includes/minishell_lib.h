/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:37:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/03 21:43:36 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LIB_H
# include "libft.h"
# include "ft_printf.h"
# include "define.h"
typedef struct s_list_arg
{
	struct s_list_arg *next;
	struct s_list_arg *prev;
	char **key_and_val;// keyname ex : ls
	char *val; // value of the keyname - obsolette
	char *opt; // option ex -a
	//char *arg; to delete
	char *full_env_var; // list of environement variable before separating key/value
	
}			t_list_arg;

typedef struct s_data
{
	t_list_arg *lst;
} t_data;


/*************************** INIT FUNC ***********************/

/*************************** PARSING FUNC ***************/
t_list_arg *parser_list_init(t_data *data, char **argv);
#endif
