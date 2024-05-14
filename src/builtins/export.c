/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:46:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/14 11:54:46 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

//export sans ARGS
//export avec ARGS
//parsing des ARGS
//export +=
//env -i export

static void	print_lst_export(t_list_arg *lst)
{
	while (lst)
	{   
        ft_printf("declare -x ");
		ft_printf("%s=", lst->key_and_val[0]);
		ft_printf("%s\n", lst->key_and_val[1]);
		lst = lst->next;
	}
}

void	cmd_export(t_data *data, char *input)
{
	int i; 
	i = ZERO_INIT;
	
	if(ft_strncmp(input, "export", 7) == 0 && data->lst != NULL)
		print_lst_export(data->lst);
}