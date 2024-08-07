/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:45:08 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/11 14:24:12 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

char	*ft_strdup_cust(const char *source)
{
	int		i;
	char	*copied_s;

	i = 0;
	copied_s = malloc(ft_strlen(source) + 1);
	if (!copied_s)
		return (NULL);
	while (source[i])
	{
		while (source[i] == ' ' || source[i] == '\t')
			i++;
		copied_s[i] = source[i];
		i++;
	}
	copied_s[i] = '\0';
	return (copied_s);
}

t_list_arg	*ft_lst_cut_new(char *content)
{
	t_list_arg	*new_node;

	new_node = (t_list_arg *)malloc(sizeof(t_list_arg));
	if (!new_node)
		return (NULL);
	new_node->key_and_val = NULL_INIT;
	new_node->next = NULL_INIT;
	new_node->input_splited = ft_strdup(content);
	if (!new_node->input_splited)
	{
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	ft_lstadd_cut_back(t_list_arg **lst, t_list_arg *new_node)
{
	t_list_arg	*tmp;

	if (lst == NULL || new_node == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

int	cutting_input(t_data *data, char *ex_input)
{
	int			i;
	char		**split;
	t_list_arg	*new_node;

	i = 0;
	split = split_pipe_cust(ex_input, '|');
	if (!split)
		return (-1);
	ft_clear_tokenizer(data);
	data->tokenizer = ft_lst_cut_new(split[i]);
	i = 1;
	while (split[i])
	{
		new_node = ft_lst_cut_new(split[i]);
		if (new_node)
		{
			ft_lstadd_cut_back(&data->tokenizer, new_node);
		}
		i++;
	}
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (0);
}
