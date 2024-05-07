/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/07 17:11:05 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

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
			return (free(to_compare), free(input), ft_strdup(tmp->key_and_val[1]));
		tmp = tmp->next;
	}
	return (free(to_compare), free(input), NULL);
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
	return (result = search_occurence(input, start, end, data));
}

char	*parser(char *input, t_data *data)
{
	int		i;
	char	*result;

	result = NULL;
	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	while (input[i])
	{
		if (input[i] == '$')
		{
			result = expansion(input, data, i);
			return (result);
		}
		i++;
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
						// debug [$]> print debug > [expansion]
}
