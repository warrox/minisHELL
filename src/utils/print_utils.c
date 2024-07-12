/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:56:57 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/11 17:24:39 by cyferrei         ###   ########.fr       */
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
