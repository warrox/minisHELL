/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:50:12 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 10:55:43 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

bool	if_pipe(char c)
{
	return (c == '|');
}

int	pipe_alone(char *input, int i)
{
	i++;
	while (ft_isws(input[i]))
		i++;
	if (input[i] && ft_isascii(input[i]))
		return (0);
	return (-1);
}

void	init_quote(t_quote *tool_box, char *str)
{
	tool_box->len = strlen(str);
	tool_box->start = 0;
	tool_box->end = tool_box->len - 1;
	tool_box->sf = 0;
	tool_box->df = 0;
}

void	free_cleaned_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

void	free_cleaned_str(char *str)
{
	if (str)
	{
		free(str);
	}
}
