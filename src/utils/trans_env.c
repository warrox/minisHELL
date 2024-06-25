/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:01:05 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/25 15:27:28 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void build_tab_env(t_data *data)
{
    t_list_arg *tmp = data->lst;
    int size = 0;
    char *tmp1;
    char *tmp2;
    int i = 0;

    while (tmp) {
        size++;
        tmp = tmp->next;
    }

    tmp = data->lst;
    data->exec->my_envp = (char **)malloc(sizeof(char *) * (size + 1)); // Allocate extra space for NULL terminator
    if (!data->exec->my_envp)
        return;

    while (tmp) {
        tmp1 = ft_strjoin(tmp->key_and_val[0], "=");
        tmp2 = ft_strjoin(tmp1, tmp->key_and_val[1]);
        free(tmp1);
        data->exec->my_envp[i] = tmp2; // Assign the joined string to the array
        i++;
        tmp = tmp->next;
    }
    data->exec->my_envp[i] = NULL; // NULL terminate the array
}
void 	print_env(t_data *data) 
{
    int i = 0;
    while (data->exec->my_envp[i] != NULL) 
	{
        printf("%s\n", data->exec->my_envp[i]);
        i++;
    }
}