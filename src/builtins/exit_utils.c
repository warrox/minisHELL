/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:20:20 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/12 13:57:46 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	exit_num(t_data *data, char *nbr_char)
{
	ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
	free(nbr_char);
	free_prompt(data);
	free(data->signal);
	free_exec(data);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
	data->exit_status = 2;
	exit(data->exit_status);
}

void	exit_quote(t_data *data, char *nbr_char, int nbr)
{
	data->exit_status = nbr % 256;
	free(nbr_char);
	free_prompt(data);
	free(data->signal);
	free_exec(data);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
	exit(data->exit_status);
}

void	exit_minus(t_data *data, int nbr, char *nbr_char)
{
	data->exit_status = nbr % 256;
	free(nbr_char);
	free_prompt(data);
	free(data->signal);
	free_exec(data);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
	exit(EXIT_FAILURE);
}

void	exit_plus(t_data *data, char *nbr_char, int nbr)
{
	data->exit_status = nbr % 256;
	free(nbr_char);
	free_prompt(data);
	free(data->signal);
	free_exec(data);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
	exit(EXIT_FAILURE);
}

void	exit_normal(t_data *data, char *nbr_char, int nbr)
{
	free(nbr_char);
	free_prompt(data);
	free(data->signal);
	free_exec(data);
	free_tmp_struct(data);
	ft_lst_arg_clear(&data->lst);
	ft_clear_tokenizer(data);
	data->exit_status = nbr % 256;
	exit(data->exit_status);
}
