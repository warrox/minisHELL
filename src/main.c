/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:30 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/26 14:28:37 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"
#include <stdio.h>

// int code_exit(int flag, int value)
// {
// 	static int exitnb;
//
// 	if (flag != 0)
// 		exitnb = value;
// 	return (exitnb);
// }

void	erase_file_array(char **array, char **array_2)
{
	int	i;
	// code_exit(1, 127);// code exit
	// int nbr = code_exit(0, 0); // exemple from nathan

	i = 0;
	if (!array || !array_2)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	i = 0;
	while (array_2[i])
	{
		free(array_2[i]);
		i++;
	}
	free(array);
	free(array_2);
}
void	ft_clear_tokenizer(t_data *data)
{
	t_list_arg	*current;
	t_list_arg	*next;
	int			i;

	if (!data || !data->tokenizer)
		return ;
	current = data->tokenizer;
	while (current != NULL)
	{
		i = 0;
		next = current->next;
		if (current->input_splited)
			free(current->input_splited);
		if (current->array_sign)
			free(current->array_sign);
		if (current->final_cmd)
			free(current->final_cmd);
		if(current->key_and_val)
		{
			free(current->key_and_val[0]);
			free(current->key_and_val[1]);
		}
		if (current->file_array)
		{
			erase_file_array(current->file_array, current->cmd_array);
		}
		free(current);
		current = next;
	}
	data->tokenizer = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	data.exit_status = 0;
	if (argc > 1)
	{
		ft_printf("Too many arguments... exit the program\n");
		exit(EXIT_FAILURE);
	}
	(void)argv;
	parser_list_init(&data, envp);
	display_prompt(&data);
	ft_lst_arg_clear(&data.lst);
	return (0);
}
