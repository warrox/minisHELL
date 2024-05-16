/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:46:41 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/16 20:38:03 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	cmd_unset(t_data *data, char *input)
{
	char **split = NULL_INIT;
	int i = 0;
	t_list_arg *tmp = data->lst;
	
	if(ft_strcmp(input, "unset") == 0 && data->lst != NULL)
	{
		split = ft_split(input, ' ');
		if (!split)
			dprintf(2, "tests\n");
			//return;
		if (split[i + 1] == NULL)
			return;
		while(tmp)
		{
			printf("%s\n", split[i]);
			printf("%s\n", tmp->key_and_val[0]);
			if(ft_strcmp(split[i], tmp->key_and_val[0]))
			{
				printf("OK\n");
				free_split(split);
				break;
			}
			tmp = tmp->next;
		}
		free_split(split);
	}
}
