/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:37:08 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/03 20:02:05 by cyferrei         ###   ########.fr       */
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
	char *arg_var;
	char *arg_val;
	char *opt;
	char *arg;	
	
}			t_list_arg;

typedef struct s_data
{
	t_list *arg;
	char *usr_name;
	char *usr_prompt;
	char *usr_pwd;
	char *final_usr_prompt;
}				t_data;

/*all prototypes functions*/

int	display_prompt(t_data *data, char **envp);


#endif