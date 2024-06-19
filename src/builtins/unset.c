/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:46:41 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/18 18:10:47 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

static void	free_node(t_list_arg *node)
{
	if (!node)
		return ;
	if (node->key_and_val)
	{
		if (node->key_and_val[0])
		{
			free(node->key_and_val[0]);
			free(node->key_and_val[1]);
		}
		free(node->key_and_val);
	}
	free(node);
}

static void	unset_var(t_list_arg **head, t_list_arg *node_to_delete)
{
	t_list_arg	*prev;

	if (!head || !node_to_delete)
		return ;
	if (node_to_delete == *head)
		*head = node_to_delete->next;
	else
	{
		prev = *head;
		while (prev && prev->next != node_to_delete)
			prev = prev->next;
		if (prev)
			prev->next = node_to_delete->next;
	}
	free_node(node_to_delete);
}

int	cmd_unset(t_data *data)
{
	if (data->tokenizer->cmd_array[0] == NULL)
		return (0);
	t_list_arg	*tmp;

	tmp = NULL_INIT;
	tmp = data->lst;
	if (ft_strncmp(data->tokenizer->final_cmd, "unset", 5) == 0
		&& data->lst != NULL)
	{
		if (!data->tokenizer->cmd_array[1])
		{
			return (1);
		}
		while (tmp)
		{
			if (ft_strcmp(data->tokenizer->cmd_array[1],
					tmp->key_and_val[0]) == 0)
			{
				unset_var(&data->lst, tmp);
				return (1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
