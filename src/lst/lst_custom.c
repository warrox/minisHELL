/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_custom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:35 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/10 16:35:57 by whamdi           ###   ########.fr       */
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
	new->count_size = 0;
	new->key_and_val = NULL_INIT;
	new->next = NULL_INIT;
	new->key_and_val = split_first_equal(content);
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
	i = ZERO_INIT;
}

void	print_lst(t_data *data, t_list_arg *lst)
{
	if (is_a_builtin(data->tokenizer) != -1
		&& is_a_builtin(data->tokenizer) != 2)
	{
		while (lst)
		{
			ft_putstr_fd(lst->key_and_val[0], data->exec->outfile);
			ft_putstr_fd("=", data->exec->outfile);
			ft_putstr_fd(lst->key_and_val[1], data->exec->outfile);
			ft_putstr_fd("\n", data->exec->outfile);
			lst = lst->next;
		}
	}
	else
	{
		while (lst)
		{
			ft_printf("%s=", lst->key_and_val[0]);
			ft_printf("%s\n", lst->key_and_val[1]);
			lst = lst->next;
		}
	}
}

void	print_lst_token(t_list_arg *lst)
{
	while (lst)
	{
		ft_printf("input_splitted : %s\n", lst->input_splited);
		lst = lst->next;
	}
}
