/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_custom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:35 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/09 14:17:07 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	ft_lstadd_arg_back(t_list_arg **lst, t_list_arg *new)
{
	t_list_arg	*tmp;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = ft_lst_arg_last((*lst));
			tmp->next = new;
		}
	}
}

t_list_arg	*ft_lst_arg_new(t_list_arg *new, char *content)
{
	new = (t_list_arg *)malloc(sizeof(t_list_arg));
	if (!new)
		return (NULL);
	new->key_and_val = NULL_INIT;
	new->next = NULL_INIT;
	new->key_and_val = ft_split(content, '=');
	return (new);
}

void	parser_list_init(t_data *data, char **envp)
{
	int	i;

	i = ZERO_INIT;
	data->lst = NULL;
	while (envp[i])
	{
		ft_lstadd_arg_back(&data->lst, ft_lst_arg_new(data->lst, envp[i]));
		i++;
	}
}

void	print_lst(t_list_arg *lst)
{
	while (lst)
	{
		ft_printf("%s=", lst->key_and_val[0]);
		ft_printf("%s\n", lst->key_and_val[1]);
		lst = lst->next;
	}
}
