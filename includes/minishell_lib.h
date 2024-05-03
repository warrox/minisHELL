/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:37:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/03 20:04:34 by whamdi           ###   ########.fr       */
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
	char *arg_var;
	char *arg_val;
	char *opt;
	char *arg;	
	
}			t_list_arg;

typedef struct s_data
{
	t_list *arg;
} t_data;


/*************************** INIT FUNC ***********************/

/*************************** PARSING FUNC ***************/
t_list *parser_list_init(t_data *data, char **argv);
#endif
