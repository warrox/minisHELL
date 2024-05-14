/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/14 13:46:16 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"
#include <stdio.h>


t_data *init_signal(t_data *data)
{
	data->signal = (t_signal *)malloc(sizeof(t_signal));
	if (!data->signal)
		return (NULL);
	data->signal->signal = ZERO_INIT;
	return (data);
}

void					msg_error_handler(int *signal , t_data *data)
{
	(void) data;
	if(*signal == COMMAND_NOT_FOUND)
		printf("command not found\n"); // ecrire dans le stderror. 
	if(*signal == SYNTAX_ERROR)
	{
		printf("syntax error\n");
		//display_prompt(data);//DINGUERIE HERE IS WHY ADD HISTORY DOESTN WORK CORRECTLY
	}
	//add other signals in the future
}
int check_quote(char *input, int i,t_data *data)
{
	data->signal->signal = NULL_INIT;
	int flag;
	int flag_s;
	flag = ZERO_INIT;
	flag_s = ZERO_INIT;
	while(input[i])
	{
		if(input[i] == '\'')
		{
			if(flag == 2)
				return(1);
			flag += 1;
		}
		if(input[i] == '\"')
		{
			if(flag_s == 2)
				return(1);
			flag_s += 1;
		}
		i++;
	}
	if(flag % 2 != 0 || flag_s == 1)	
		data->signal->signal = SYNTAX_ERROR;
	return(0);

}

int check_redir(char *input, int i, t_data *data)
{	
	int flag;
	flag = 0;
	if(input[i] == '>')
	{
		i++;
		while(ft_isprint(input[i])) //check if is print is a correct usage
		{
			if(input[i] == '$')
				return(3);
			if(input[i] != ' ' && input[i] != '\t')
				flag = 1;
			if(input[i] == '|')
				break;
			i++;
		}
	}
	else
		return(0);
	if(flag  == 1)
		return(1);
	data->signal->signal = SYNTAX_ERROR;
	return(0);
}
int checker_err(char *input,t_data *data)
{
	int i;
	int is_valid;
	int not_valid;
	
	not_valid = 0;
	is_valid = 1;
	i = ZERO_INIT;
	if(check_quote(input,i,data)) // bloc inverse cense renvoye not valid
	{
		return(is_valid);
	}
	if(check_redir(input, i,data))
		return(is_valid);

	if(data->signal->signal != NULL_INIT)	
		msg_error_handler(&data->signal->signal,data);
	return(not_valid);
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
		return (result = search_occurence(input, start, end, data));
}

char	*parser(char *input, t_data *data)
{
	int		i;
	char	*result;
	
	init_signal(data);
	data->signal->signal = ZERO_INIT;
	result = NULL;
	i = 0;
	cmd_env(data, input);
	pwd_cmd(input);
	cmd_export(data, input);
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	checker_err(input,data);
	while (input[i])
	{
		if (input[i] == '$')
		{
			result = expansion(input, data, i);
			if(result == input)
			{
				//free(data->signal->signal);
				free(data->signal);
				return (input);	
			}
		}
		i++;
	}
	free(data->signal);
	return (input); // if NULL printf command not found
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
