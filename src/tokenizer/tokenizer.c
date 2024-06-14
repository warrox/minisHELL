/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:13 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/14 13:53:31 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"
#include <readline/history.h>

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
	ft_printf("HERE : %s\n", str);
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			i++;
			while (str[i] != '\"')
				buffer[j++] = str[i++];
			if (str[i] == '\"')
				i++;
		}

		tmp = sign_cmp(&str[i]);
		ft_printf("tmp int : %d, str = %s\n", tmp, &str[i]);
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
	ft_printf("FLUSH : %s\n", buffer);
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

int	cutting_input(t_data *data, char *input)
{
	int			i;
	char		**split;
	t_list_arg	*new_node;
	i = 0;
	
	if(checker_err_pipe(input, data) == 0 || check_quote(input, 0, data) == 0) 
	{
		return(-1);
	}
	split = ft_split(input, '|'); // po bon
	if (!split)
		return(-1);
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
	return(0);
}
