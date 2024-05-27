/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/27 10:12:52 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

int	check_redir(char *input, int i, t_data *data)
{
	int	flag;

	flag = 0;
	if (input[i] == '>')
	{
		i++;
		while (ft_isprint(input[i]))
		{
			if (input[i] == '$')
				return (3);
			if (input[i] != ' ' && input[i] != '\t')
				flag = 1;
			if (input[i] == '|')
				break ;
			i++;
		}
	}
	else
		return (0);
	if (flag == 1)
		return (1);
	data->signal->signal = SYNTAX_ERROR;
	return (0);
}

int	checker_err(char *input, t_data *data)
{
	int	i;
	int	is_valid;
	int	not_valid;

	not_valid = 0;
	is_valid = 1;
	i = ZERO_INIT;
	if (check_quote(input, i, data))
	{
		return (is_valid);
	}
	if (check_redir(input, i, data))
		return (is_valid);
	if (data->signal->signal != NULL_INIT)
		msg_error_handler(&data->signal->signal, data);
	return (not_valid);
}

char	*search_occurence(char *input, int start, int end, t_data *data)
{
	t_list_arg	*tmp;
	int			i;
	char		*to_compare;

	i = 0;
	tmp = data->lst;
	to_compare = ft_substr(input, start, end);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key_and_val[0], to_compare, ft_strlen(to_compare)))
			return (free(to_compare), tmp->key_and_val[1]);
		tmp = tmp->next;
	}
	return (free(to_compare), input);
}

char	*expansion(char *input, t_data *data, int i)
{
	int		start;
	int		end;
	char	*result;

	start = 0;
	end = 0;
	result = NULL;
	i++;
	if (input[i] == ' ')
		return (NULL);
	while (input[i])
	{
		if (input[i] == ' ')
			break ;
		start = i;
		while (input[i] != ' ' && input[i] != '\t' && input[i] != '\0')
			i++;
		end = i;
	}
	result = search_occurence(input, start, end, data);
	return (result);
}

char	*parser(char *input, t_data *data)
{
	int			i;
	char		*result;
	t_list_arg	*tmp;

	init_signal(data);
	data->signal->signal = ZERO_INIT;
	result = NULL;
	i = 0;
	tmp = data->tokenizer;
	cutting_input(data, input);
	tmp = data->tokenizer;
	while (tmp)
	{
		if (tmp->input_splited[i] == '$' && tmp->input_splited[i + 1] != '$')
		{
			checker_err(tmp->input_splited, data);
			tmp->result = expansion(tmp->input_splited, data, i);
			if (tmp->result == tmp->input_splited)
			{
				free(data->signal);
				return (tmp->input_splited);
			}
			else
				tmp->input_splited = tmp->result;
		}
		tmp = tmp->next;
	}
	parse_cmd_arg(data);
	is_a_builtin(data);
	while (!data->tokenizer->cmd_and_arg)
	{
		ft_printf("BiM\n");
		data->tokenizer = data->tokenizer->next;
	}
	return (input);
}
