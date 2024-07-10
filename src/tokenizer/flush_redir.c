/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:57:55 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 13:41:03 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	handle_double_quotes_flush(char *str, char *buffer, t_data *data)
{
	data->pansement = 0;
	data->pansement_2 = 0;
	buffer[data->j++] = str[data->i];
	data->i++;
	while (str[data->i] && str[data->i] != '\"')
	{
		buffer[data->j++] = str[data->i];
		data->i++;
	}
	if (str[data->i] == '\"')
	{
		buffer[data->j++] = str[data->i];
		data->pansement = 1;
		data->pansement_2 = 1;
		data->i++;
	}
}

void	handle_single_quotes_flush(char *str, char *buffer, t_data *data)
{
	data->pansement = 0;
	buffer[data->j++] = str[data->i];
	data->i++;
	while (str[data->i] && str[data->i] != '\'')
	{
		buffer[(data->j)++] = str[data->i];
		data->i++;
	}
	if (str[data->i] == '\'')
	{
		buffer[data->j++] = str[data->i];
		data->pansement = 1;
		data->i++;
	}
}

int	handle_signs(char *str, int *i)
{
	int	tmp;

	tmp = sign_cmp(&str[*i]);
	if (tmp)
	{
		*i += tmp;
		*i += get_word_size(&str[*i]);
	}
	return (tmp);
}

char	*flush_redir(char *str, t_data *data)
{
	char	buffer[2048];
	int		tmp;
	int		len;

	data->i = 0;
	data->j = 0;
	data->pansement = 0;
	len = ft_strlen(str);
	while (data->i < len)
	{
		if (str[data->i] == '\"')
			handle_double_quotes_flush(str, buffer, data);
		else if (str[data->i] == '\'')
			handle_single_quotes_flush(str, buffer, data);
		else
			tmp = handle_signs(str, &data->i);
		if (!tmp)
		{
			buffer[data->j++] = str[data->i];
			data->i++;
		}
	}
	buffer[data->j] = 0;
	return (ft_strdup(buffer));
}
