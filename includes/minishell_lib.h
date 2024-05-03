/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:37:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/03 15:38:20 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LIB_H
# include "libft.h"
# include "ft_printf.h"

typedef struct s_list_arg
{
	struct s_list_arg *next;
	struct s_list_arg *prev;
	char *arg_var;
	char *arg_val;
	char *opt;
}			t_list_arg;

typedef struct s_data
{
		
} t_data;


/*************************** INIT FUNC ***********************/

/*************************** PARSING FUNC ***************/
#endif
