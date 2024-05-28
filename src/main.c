/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:30 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/28 15:05:31 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"


void	erase_file_array(char **array)
{
	int i; 
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
void	ft_clear_tokenizer(t_list_arg *tokenizer)
{
	t_list_arg	*current;
	t_list_arg	*next;

	current = tokenizer;
	next = tokenizer;
	while (next != NULL)
	{
		free(current->input_splited);
		free(current->array_sign);
		free(current->final_cmd);
		erase_file_array(current->file_array);	
		next = current->next;
		free(current);
		current = next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

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
