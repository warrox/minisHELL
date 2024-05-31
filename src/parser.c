/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/31 17:34:48 by whamdi           ###   ########.fr       */
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

char	*search_occurence(char *input,t_data *data)
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


int expand_stopper(char c)
{
	if(c == '{' ||(c == '}' || c == '.' || c == ' ' || c == '\t'))
	{
		return(1);
	}
	return(0);
}
char	*expansion(char *input, t_data *data)
{
	int i = 0;
	int end = 0;
	char *result;

	while (input[i] && input[i] != expand_stopper(input[i]))
	{
		end++;
		i++;
	}
	char *key = ft_substr(input, 0, end);
	result = ft_strdup(search_occurence(key, data));
	free(key);
	return (result);
}
t_list_arg *init_tokenizer( void )// NEW FUNC
{
	t_list_arg *tokenizer = ft_calloc(1, sizeof(t_list_arg));

	tokenizer->final_cmd = ZERO_INIT;
	tokenizer->array_sign = ZERO_INIT;
	tokenizer->file_array = NULL_INIT;
	tokenizer->count_size = ZERO_INIT;
	tokenizer->cmd_and_arg = NULL_INIT;
	tokenizer->key_and_val = NULL_INIT;
	tokenizer->input_splited = NULL_INIT;
	return (tokenizer);
	
}
void expander(t_data *data) // REMPLACER TOUTES LES VARS PAR final_cmd et non input_splitted
{
	t_list_arg	*tmp;
	int i;
	int j;
	i = 0;
	j = 0;
	tmp = data->tokenizer;
	while (tmp)
	{
		i = 0;
		ft_bzero(tmp->result, 4096);
		while (tmp->final_cmd[i])
		{
			if (tmp->final_cmd[i] == '\'')
			{
				while (tmp->final_cmd[++i] != '\'')
					tmp->result[j++] = tmp->final_cmd[i++];
			}
			if (tmp->final_cmd[i] == '$')
			{
				char *expanded = expansion(&tmp->final_cmd[++i], data);
				j += ft_strlen(expanded);
				ft_strlcat(tmp->result, expanded, ft_strlen(expanded) + ft_strlen(tmp->result) + 1);
				free(expanded);
				while (tmp->final_cmd[i] && tmp->final_cmd[i] != ' ')
					i++;
			}
			tmp->result[j++] = tmp->final_cmd[i++];
		}
		tmp->result[j] = '\0';
		printf("FDP = |%s|\n", tmp->result);
		tmp = tmp->next;
	}
}
char	*parser(char *input, t_data *data)
{
	char		*result;	
	if (*input == '\0')	
		return(input);
	result = NULL;
	//tmp = data->tokenizer;
	cutting_input(data, input);
	parse_cmd_arg(data); //ADAPT YOUR EXPANSION AFTER THE PARSE_CMD_ARG
	expander(data);	
	is_a_builtin(data);
	return (input);
}
