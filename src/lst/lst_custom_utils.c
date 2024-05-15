/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_custom_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:47:05 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/14 10:40:14 by whamdi           ###   ########.fr       */
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
	lst->prev = NULL;
	while (lst->key_and_val && lst->key_and_val[i])
	{
		free(lst->key_and_val[i]);
		i++;
	}
	free(lst->key_and_val);
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
