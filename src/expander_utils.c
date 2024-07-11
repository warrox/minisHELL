/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:19:00 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/11 09:46:02 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

bool	is_single_quote(char c)
{
	return (c == '\'');
}

bool	isvariable(char *input, int *i)
{
	return (!ft_strncmp(&input[*i], "$", 1));
}

char	*passtilnextquote(char *input, int *i, char *buffer, int *j)
{
	(*i)++;
	while (input[*i] && !is_single_quote(input[*i]))
	{
		buffer[(*j)++] = input[*i];
		(*i)++;
	}
	if (input[*i] == '\'')
	{
		(*i)++;
	}
	buffer[*j] = ' ';
	(*j)++;
	buffer[*j] = '\0';
	return (buffer);
}

bool	isheredoc(char *input, int *i)
{
	return (!ft_strncmp(&input[*i], "<<", 2));
}

void	init_expand(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->sq = 0;
	data->dq = 0;
}
