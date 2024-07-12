/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:19:10 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/12 14:55:33 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"
#include <stdio.h>

void	passvardoc(char *input, int *i, char *buffer, int *j)
{
	buffer[(*j)] = input[(*i)];
	(*i) += 1;
	(*j)++;
	buffer[(*j)] = input[(*i)];
	(*i) += 1;
	(*j)++;
	while (input[*i] && ft_isws(input[*i]))
	{
		(*i)++;
	}
	while (input[*i] && !ft_isws(input[*i]))
	{
		buffer[(*j)++] = input[(*i)++];
	}
	buffer[*j] = ' ';
	(*j)++;
	buffer[*j] = '\0';
}

char	*buff_copy(char *input)
{
	char	*buffer;
	int		len;
	int		flag;

	len = 0;
	flag = 0;
	while (input[len] && input[len] != ' ')
	{
		if (input[len] == '$' || input[len] == '\'')
		{
			break ;
		}
		if (input[len] == '\"' || input[len] == '\'')
		{
			flag = 1;
		}
		len++;
	}
	if (flag == 1)
		len--;
	buffer = ft_substr(input, 0, len);
	return (buffer);
}

void	expandvariable(t_data *data, char *input, char *buffer)
{
	t_list_arg	*current;
	char		*b_copy;

	current = data->lst;
	initexpandvariable(data);
	b_copy = buff_copy(&input[data->i]);
	while (current)
	{
		data->key_len = ft_strlen(current->key_and_val[0]);
		if (!ft_strncmp(&input[data->i], current->key_and_val[0], data->key_len)
			&& ((!data->dq || data->dq)
				&& (ft_strlen(current->key_and_val[0]) == ft_strlen(b_copy))))
		{
			data->flag = 1;
			ft_strlcat(buffer, current->key_and_val[1], 4096);
			data->j += ft_strlen(current->key_and_val[1]);
			data->i += data->key_len;
			break ;
		}
		current = current->next;
	}
	free(b_copy);
	passpartstring(&data->flag, &data->i, input);
}

void	expandexitcode(int *i, t_data *data, char *strexpanded, int *j)
{
	char	*itoa_exitcode;
	int		k;

	k = 0;
	(*i) += 2;
	itoa_exitcode = ft_itoa(data->exit_status);
	while (itoa_exitcode[k])
	{
		strexpanded[(*j)++] = itoa_exitcode[k++];
	}
}

void	expander(t_data *data, char *input)
{
	char	strexpanded[4096];

	ft_bzero(strexpanded, 4096);
	init_expand(data);
	while (input[data->i])
	{
		if (is_double_quote(input[data->i]) && !data->sq)
			data->dq = !data->dq;
		else if (is_single_quote(input[data->i]) && !data->dq)
			data->sq = !data->sq;
		else if (isheredoc(input, &data->i))
			passvardoc(input, &data->i, strexpanded, &data->j);
		else if (isexitcode(input, &data->i) && !data->sq)
			expandexitcode(&data->i, data, strexpanded, &data->j);
		if (isvariable(input, &data->i) && !data->sq && (input[data->i + 1]
				&& ft_isalnum(input[data->i + 1])))
			expandvariable(data, input, strexpanded);
		else
			strexpanded[data->j++] = input[data->i++];
		if (data->i > (int)ft_strlen(input))
			break ;
	}
	strexpanded[data->j] = '\0';
	data->tokenizer->final_cmd = ft_strdup(strexpanded);
}
