/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:13 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/04 15:10:09 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	sort_sign(t_list_arg *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	tmp->count_size = count_sign(tmp->input_splited);
	i = 0;
	tmp->array_sign = ft_calloc(tmp->count_size + 1, sizeof(int));
	while (tmp->count_size && tmp->input_splited[i])
	{
		if (ft_strncmp(&tmp->input_splited[i], "<<", 2) == 0)
		{
			tmp->array_sign[j++] = HEREDOCS;
			i += 2;
		}
		else if (ft_strncmp(&tmp->input_splited[i], ">>", 2) == 0)
		{
			tmp->array_sign[j++] = APPEND;
			i += 2;
		}
		else if (ft_strncmp(&tmp->input_splited[i], "<", 1) == 0)
		{
			tmp->array_sign[j++] = STDINS;
			i += 1;
		}
		else if (ft_strncmp(&tmp->input_splited[i], ">", 1) == 0)
		{
			tmp->array_sign[j++] = STDOUTS;
			i += 1;
		}
		else
			i++;
	}
}

int	get_word_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isws(str[i]))
		i++;
	while (str[i] && !ft_isws(str[i]))
		i++;
	return (i);
}

char	*flush_redir(char *str)
{
	char	buffer[2048];
	int		i;
	int		tmp;
	int		j;

	i = 0;
	tmp = 0;
	j = 0;
	while (str[i])
	{
		tmp = sign_cmp(&str[i]);
		if (tmp)
		{
			i += tmp;
			i += get_word_size(&str[i]);
		}
		else
		{
			buffer[j++] = str[i];
			i++;
		}
	}
	buffer[j] = 0;
	return (ft_strdup(buffer));
}

void	parse_cmd_arg(t_data *data)
{
	t_list_arg	*tmp;

	tmp = data->tokenizer;
	while (tmp)
	{
		sort_sign(tmp);
		create_signed(tmp);
		tmp->final_cmd = flush_redir(tmp->input_splited);
		tmp = tmp->next;
	}
}

void	cutting_input(t_data *data, char *input)
{
	int			i;
	char		**split;
	t_list_arg	*new_node;

	i = 0;
	checker_err_pipe(input, data);
	split = ft_split(input, '|'); // po bon
	if (!split)
		return ;
	free(data->tokenizer);
	data->tokenizer = ft_lst_cut_new(split[i]);
	i = 1;
	while (split[i])
	{
		new_node = ft_lst_cut_new(split[i]);
		if (new_node)
			ft_lstadd_cut_back(&data->tokenizer, new_node);
		i++;
	}
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
