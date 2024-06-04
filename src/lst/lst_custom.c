/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_custom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:35 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/03 17:40:43 by whamdi           ###   ########.fr       */
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

void	print_lst_token(t_list_arg *lst)
{
	while (lst)
	{
		ft_printf("input_splitted : %s\n", lst->input_splited);
		lst = lst->next;
	}
}
void	print_lst_cmdarg(t_list_arg *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		// ft_printf("cmd_arg[0] : %s\n", lst->cmd_and_arg[0]);
		// ft_printf("cmd_arg[1] : %s\n", lst->cmd_and_arg[1]);
		ft_printf("FINAL_CMD = %s\n", lst->final_cmd);
		ft_printf("RESULT : %s\n", lst->result);
		i = 0;
		if (lst->array_sign)
		{
			ft_printf("----Array Signs----\n");
			while (i < lst->count_size)
			{
				ft_printf("[%d]\t[%s]\n", lst->array_sign[i],
					lst->file_array[i]);
				i++;
			}
		}
		i = 0;
		while (lst->cmd_array[i])
		{
			ft_printf("----ARRAY_CMD[%d]----\n", i);
			ft_printf("[%s]\n", lst->cmd_array[i]);
			i++;
		}
		lst = lst->next;
	}
}
