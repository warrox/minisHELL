/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:46:54 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 18:48:57 by whamdi           ###   ########.fr       */
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

char	*search_occurence(char *input, t_data *data)
{
	t_list_arg	*tmp;
	int			i;

	i = 0;
	tmp = data->lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key_and_val[0], input, ft_strlen(input)))
			return (tmp->key_and_val[1]);
		tmp = tmp->next;
	}
	return (NULL);
}
