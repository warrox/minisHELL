/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:56:57 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/08 15:00:27 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"
#include <stdio.h>

void	print_prompt_struct(t_data *data)
{
	t_prompt	*tmp;

	tmp = data->prompt;
	printf("----------------------------------------\n");
	printf("            PROMPT STRUCTURE            \n");
	printf("----------------------------------------\n");
	printf("[usr_name] = %s\n", tmp->usr_name);
	printf("[usr_pwd] = %s\n", tmp->usr_pwd);
	printf("[usr_build_one] = %s\n", tmp->usr_build_one);
	printf("[usr_build_two] = %s\n", tmp->usr_build_two);
	printf("[usr_prompt] = %s\n", tmp->usr_prompt);
	printf("----------------------------------------\n");
}

void	print_exec_utils(t_data *data)
{
	t_list_arg	*tmp;
	int			i;

	int j = 0;
	i = 0;
	tmp = data->tokenizer;
	while (tmp)
	{
		if (tmp->array_sign)
		{
			if(tmp->count_size > 0)
			{
				dprintf(2, "ICI\n");
				printf("---------------REDIRECTION ARRAY on node [%d]----------------\n",j);
				i = 0;
				while (i < tmp->count_size)
				{
					ft_printf("[%d]\t[%s]\n", tmp->array_sign[i],tmp->file_array[i]);
					i++;
				}
			}
		}
		printf("---------------COMMAND & ARG ARRAY on node[%d]---------------------\n",j++);
		i = 0;
		while (tmp->cmd_array[i])
		{
			printf("[CMD_ARRAY][%d] = %s\n", i, tmp->cmd_array[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
