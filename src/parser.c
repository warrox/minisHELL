/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/24 14:54:34 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

int check_redir(char *input, int i, t_data *data)
{	
	int flag;
	flag = 0;
	if (input[i] == '>')
	{
		i++;
		while (ft_isprint(input[i])) // check if is print is a correct usage
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
	if (check_quote(input, i, data)) // bloc inverse cense renvoye not valid
	{
		return (is_valid);
	}
	if (check_redir(input, i, data))
		return (is_valid);
	if (data->signal->signal != NULL_INIT)
		msg_error_handler(&data->signal->signal, data);
	return (not_valid);
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
	result = search_occurence(input, start, end, data);	
	return (result);
}

char	*parser(char *input, t_data *data)
{
	int		i;
	char	*result;
	t_list_arg *tmp;
	
	init_signal(data);
	data->signal->signal = ZERO_INIT;
	result = NULL;
	i = 0;
	tmp = data->tokenizer;
	cmd_env(data, input);
	pwd_cmd(input);
	cmd_export(data, input);
	cmd_unset(data, input);	
	cutting_input(data, input);// cut at pipe
	// ft_printf("data->tokenizer = %p\n", data->tokenizer);
	print_lst_token(data->tokenizer);
	tmp = data->tokenizer;
	while(tmp) // $ EXPAND
	{	
		if (tmp->input_splited[i] == '$' && tmp->input_splited[i + 1] != '$')
		{
			checker_err(tmp->input_splited, data);
			tmp->result = expansion(tmp->input_splited, data, i);
			if(tmp->result == tmp->input_splited)
			{
				free(data->signal);
				return (tmp->input_splited);	
			}
			else 
				tmp->input_splited = tmp->result;
		}
		// ft_printf("resx = %s\n", tmp->input_splited);
		tmp = tmp->next;
	}
	//tri_sign(data);
	parse_cmd_arg(data);
	// ft_printf("data->tokenizer = %p\n", data->tokenizer);
	print_lst_token(data->tokenizer);
	while(!data->tokenizer->cmd_and_arg)
	{
		ft_printf("BiM\n");
		data->tokenizer = data->tokenizer->next;
	}
	//ft_printf("cmd[0] : %s\n",data->tokenizer->cmd_and_arg[0]); 
	print_lst_cmdarg(data->tokenizer);
	// ft_printf("sign : %d\n",data->tokenizer->redir_sign);
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
