/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:46:41 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/20 13:04:47 by cyferrei         ###   ########.fr       */
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
			free(node->key_and_val[0]);
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

void	cmd_unset(t_data *data, char *input)
{
	char		**split;
	int			i;
	t_list_arg	*tmp;

	tmp = NULL_INIT;
	split = NULL_INIT;
	i = 0;
	tmp = data->lst;
	if (ft_strncmp(input, "unset", 5) == 0 && data->lst != NULL)
	{
		split = ft_split(input, ' ');
		if (!split)
			return ;
		if (split[i + 1] == NULL)
			return (free_split(split));
		while (tmp)
		{
			if (!ft_strcmp(split[i + 1], tmp->key_and_val[0]))
				return (unset_var(&data->lst, tmp), free_split(split));
			tmp = tmp->next;
		}
		free_split(split);
	}
}
