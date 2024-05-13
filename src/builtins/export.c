/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:46:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/13 16:55:36 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

//export sans ARGS
//export avec ARGS
//parsing des ARGS
//export +=
//env -i export

static t_list_arg *sort_lst(t_list_arg *lst) 
{
    t_list_arg *export_lst;
    t_list_arg *tmp = NULL;
	t_list_arg *prev = NULL;
    int swapped = 1;
	
    if (lst == NULL || lst->next == NULL)
        return lst;
    while (swapped) 
	{
        swapped = 0;
        export_lst = lst;
        while (export_lst->next != NULL) 
		{
            if (ft_strncmp(export_lst->key_and_val[0], export_lst->next->key_and_val[0], 1) > 0) 
			{
                tmp = export_lst->next;
                export_lst->next = tmp->next;
                tmp->next = export_lst;
                if (export_lst == lst)
                    lst = tmp;
                else 
				{
                    prev = lst;
                    while (prev->next != export_lst)
                        prev = prev->next;
                    prev->next = tmp;
                }
                export_lst = tmp;
                swapped = 1;
            }
            else
                export_lst = export_lst->next;
        }
    }
    return lst;
}


static void	print_lst_export(t_list_arg *lst)
{
	sort_lst(lst);
	while (lst)
	{
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