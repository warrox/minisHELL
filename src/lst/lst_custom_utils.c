/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_custom_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:47:05 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/04 16:47:22 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	ft_lst_arg_delone(t_list_arg *lst)
{
	int	i;

	i = ZERO_INIT;
	if (!lst)
		return ;
	lst->next = NULL;
	if (lst->key_and_val && lst->key_and_val[i])
	{
		while (lst->key_and_val && lst->key_and_val[i])
		{
			free(lst->key_and_val[i]);
			i++;
		}
		free(lst->key_and_val);
	}
	free(lst);
}

void	ft_lst_arg_clear(t_list_arg **lst)
{
	t_list_arg	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lst_arg_delone(*lst);
		*(lst) = tmp;
	}
}

t_list_arg	*ft_lst_arg_last(t_list_arg *lst)
{
	t_list_arg	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}
