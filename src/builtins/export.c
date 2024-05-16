/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:46:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/16 16:03:56 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

//export sans ARGS OK
//export avec ARGS
//parsing des ARGS
//export +=
//env -i export

static void	set_value(t_data *data, char *value, char *new)
{
	t_list_arg *tmp;

	tmp = data->lst;
	while (tmp && ft_strcmp(tmp->key_and_val[0], value) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return;
	else
	{
		free(tmp->key_and_val[1]);
		tmp->key_and_val[1] = ft_strdup(new);
	}
}

static int check_egals(char *input)
{
	int i;

	i = ZERO_INIT;
	while(input[i])
	{
		if(input[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void free_split(char **split)
{
	int i;
	
	i = ZERO_INIT;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

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

void cmd_export(t_data *data, char *input) 
{
	char **split = NULL;
   	char **arg = NULL;
    t_list_arg *tmp = data->lst;
	int i = 1;
	int j = 1;

	if(ft_strcmp(input, "") == 0)
		return;
    if (ft_strcmp(input, "export") == 0 && data->lst != NULL) 
        print_lst_export(data->lst);
	else
	{
		split = ft_split(input, ' ');
		if (!split)
			return;
		while(split[i])
		{
			arg = ft_split(split[i], '=');
			if(!arg)
			{
				free_split(split);
				return;
			}
			tmp = data->lst;
			int count = 0;
			while(tmp)
			{
				if(ft_strcmp(arg[0], tmp->key_and_val[0]) == 0 && check_egals(split[j])) 
				{
					set_value(data, tmp->key_and_val[0], arg[1]);
					printf("MATCH\n");
					break;
				}
				tmp = tmp->next;
				count++;
			}
			if (tmp == NULL)
			{
				ft_printf("%s\n", split[i]);
				ft_lstadd_arg_back(&data->lst, ft_lst_arg_new(data->lst, split[i]));
			}
			free_split(arg);
			j++;
			i++;
			
		}
		free_split(split);
	}
}
