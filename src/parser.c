/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/07 15:39:07 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

char	*search_occurence(char *input, int start, int end, t_data *data)
{
	t_list_arg	*tmp;
	int			i;

	i = 0;
	tmp = data->lst;
	while (tmp)
	{
		if (input[start] == tmp->key_and_val[0][i])
		{
			while (start != end && input[i] == tmp->key_and_val[0][i])
			{
				start++;
				i++;
			}
			start++;
			if (input[start] == '\0' && tmp->key_and_val[0][i] == '\0')
				return (tmp->key_and_val[1]);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*expansion(char *input, t_data *data)
{
	int		i;
	char	*result;
	int		start;
	int		end;

	i = 0;
	result = NULL;
	while (input[i] != '$')
		i++;
	i++;
	if (input[i] == ' ')
	{
		while (input[i] == ' ')
			i++;
		i++;
		start = i;
		while (input[i] != ' ' || input[i] != '\n')
			i++;
		end = i;
		return (result = search_occurence(input, start, end, data));
	}
	return (result);
}

char	*parser(char *input, t_data *data)
{
	int		i;
	char	*result;

	(void)input;
	(void)data;
	result = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			result = expansion(input, data);
		}
	}
	return (result); // if NULL printf command not found
						// expansion $
						// < > << >>
						// ctrl c ctrl d ctrl \
	// echo -n
						// Cd
						// pwd
						// export
						// unset
						// env
						// exit
}
