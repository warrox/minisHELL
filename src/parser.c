/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/13 17:18:52 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

int	expand_stopper(char c)
{
	if (c == '{' || (c == '}' || c == '.' || c == ' ' || c == '\t'))
	{
		return (1);
	}
	return (0);
}
char	*expansion(char *input, t_data *data)
{
	int		i;
	int		end;
	char	*result;
	int		flag;
	char	*key;

	i = 0;
	end = 0;
	flag = 0;
	while (input[i])
	{
		if (expand_stopper(input[i]))
		{
			flag = 1;
			break ;
		}
		end++;
		i++;
	}
	key = ft_substr(input, 0, end);
	result = ft_strdup(search_occurence(key, data));
	i = 0;
	while (result[i] != 0)
		i++;
	if (flag == 1)
		result[i++] = input[end++];
	result[i++] = '\0';
	free(key);
	return (result);
}
t_list_arg	*init_tokenizer(void)
{
	t_list_arg	*tokenizer;

	tokenizer = ft_calloc(1, sizeof(t_list_arg));
	tokenizer->final_cmd = ZERO_INIT;
	tokenizer->array_sign = ZERO_INIT;
	tokenizer->file_array = NULL_INIT;
	tokenizer->count_size = ZERO_INIT;
	tokenizer->key_and_val = NULL_INIT;
	tokenizer->input_splited = NULL_INIT;
	return (tokenizer);
}
void	expander(t_data *data)
{
	t_list_arg	*tmp;
	int			i;
	int			j;
	char		*expanded;
	int			flag;
	i = 0;
	j = 0;
	flag = 0;
	tmp = data->tokenizer;
	while (tmp)
	{
		i = 0;
		ft_bzero(tmp->result, 4096);
		while (tmp->final_cmd[i])
		{
			if (tmp->final_cmd[i] == '\'')
			{
				while (tmp->final_cmd[i++] != '\'' && tmp->final_cmd[i + 1] != '\0')
				{
					if(flag % 2 != 0 && tmp->final_cmd[i + 1] == '\0')
						return;
					flag++;
					tmp->result[j++] = tmp->final_cmd[i];
				}
				flag = 1;
			}
			if (tmp->final_cmd[i] == '\"')
			{
				while (tmp->final_cmd[i++] != '\"' && tmp->final_cmd[i + 1] != '\0')
				{
					if(flag % 2 != 0 && tmp->final_cmd[i + 1] == '\0')
						return;
					flag++;
					tmp->result[j++] = tmp->final_cmd[i];
				}
				flag = 1;
			}
			if (tmp->final_cmd[i] == '$')
			{
				expanded = expansion(&tmp->final_cmd[++i], data);
				j += ft_strlen(expanded);
				ft_strlcat(tmp->result, expanded, ft_strlen(expanded)
					+ ft_strlen(tmp->result) + 1);
				free(expanded);
				while (tmp->final_cmd[i] && tmp->final_cmd[i] != ' ')
					i++;
			}
			tmp->result[j++] = tmp->final_cmd[i++];
		}	
		if(flag)
			j -= 1;
		tmp->result[j] = '\0';
		tmp->cmd_array = ft_split(tmp->result, ' ');
		j = 0;
		i = 0;
		tmp = tmp->next;
	}
}
char	*parser(char *input, t_data *data)
{
	char	*result;

	if (*input == '\0')
		return (input);
	result = NULL;
	if(cutting_input(data, input) == -1)
		return NULL;
	parse_cmd_arg(data);
	expander(data);
	is_a_builtin(data);
	return (input);
}
