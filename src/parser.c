/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/06 12:21:49 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

char * search_occurence(char *input, int start, int end, t_data *data)
{
	t_list_arg *tmp;
	int i;
	i = 0;
	tmp = data->lst;
	while(tmp)
	{
		if(input[start] == tmp->key_and_val[0][i])
		{
			while(start != end && input[i] == tmp->key_and_val[0][i])
			{
				start++;
				i++;
			}
			start++;
			if(input[start] == '\0' && tmp->key_and_val[0][i] == '\0')
				return(tmp->key_and_val[1]);
		}
		tmp = tmp->next;
	}
	return(NULL);
}

char *expansion(char *input, t_data *data)
{
	int i;
	i = 0;
	char *result;
	while(input[i] != '$')
		i++;
	i++;
	if(input[i] == ' ')
	{
		while(input[i] == ' ')
			i++;
		i++;
		int start = i;
		while(input[i] != ' ' || input[i] != '\n')
			i++;
		int end = i;
		return(result = search_occurence(input,start,end,data));
	}
		return(result);
}
char	*parser(char *input, t_data *data)
{
	(void)input;
	(void)data;
	int i;
	char *result;
	i = 0;
	while(input[i])
	{
		if(input[i] == '$')
		{
			result = expansion(input,data);
		}
	}
	return(result); // if NULL printf command not found
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
