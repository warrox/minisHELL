/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:37:05 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/12 13:57:53 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	init_struct(t_exit_data *e, t_data *data)
{
	e->i = 0;
	e->neg = 1;
	e->quote = 0;
	e->tmp = data->tokenizer->cmd_array;
	ft_bzero(e->s_nbr, 4096);
	e->nbr = 0;
	e->count = 0;
}

void	check_plus_minus(char *input, t_exit_data *e)
{
	e->i = 0;
	e->j = 3;
	while (input[e->j] && !ft_isws(input[e->j]))
		e->j++;
	e->j++;
	if (input[e->j] == '+' || input[e->j] == '-')
	{
		if (input[e->j] == '-')
			e->neg = -e->neg;
		e->j++;
	}
	if (input[e->j] == '"')
	{
		e->quote = 1;
		e->j++;
	}
	if (input[e->j] == '+' || input[e->j] == '-')
	{
		if (input[e->j] == '-')
			e->neg = -e->neg;
		e->j++;
	}
}

void	check_helper(t_exit_data *e, t_data *data, char *input)
{
	if (e->neg == -1)
		e->nbr = -e->nbr;
	e->nbr_char = ft_itoa((int)e->nbr);
	if (e->neg == -1)
	{
		if (ft_strncmp(data->tokenizer->cmd_array[1], e->nbr_char,
				ft_strlen(data->tokenizer->cmd_array[1])) != 0)
			exit_minus(data, e->nbr, e->nbr_char);
	}
	else
	{
		if (ft_strncmp(e->s_nbr, e->nbr_char, ft_strlen(e->s_nbr)) != 0)
			exit_plus(data, e->nbr_char, e->nbr);
	}
	if (input[e->j] == '\0')
		exit_normal(data, e->nbr_char, e->nbr);
	while (input[e->i] != '\0')
	{
		e->str[e->i] = input[e->i];
		e->i++;
	}
}

void	execute_exit(char *input, t_exit_data *e, t_data *data)
{
	check_plus_minus(input, e);
	while (input[e->j] && ft_isdigit(input[e->j]))
	{
		e->s_nbr[e->i] = input[e->j];
		e->i++;
		e->j++;
	}
	e->s_nbr[e->j] = '\0';
	e->nbr = ft_atoi_long(e->s_nbr);
	check_helper(e, data, input);
	e->str[e->i] = '\0';
	if (e->quote)
		exit_quote(data, e->nbr_char, e->nbr);
	else
		exit_num(data, e->nbr_char);
}

int	ft_exit(t_data *data, char *input)
{
	t_exit_data	e;

	init_struct(&e, data);
	while (e.tmp[e.i])
	{
		e.count++;
		e.i++;
	}
	e.i = 0;
	if (e.count > 2)
		exit_args(data);
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		while (ft_isprint(input[e.i]))
			e.i++;
		if (ft_strlen(input) > 4)
			execute_exit(input, &e, data);
		else if (input[e.i] == '\0')
			exit_helper(data);
	}
	return (256);
}
