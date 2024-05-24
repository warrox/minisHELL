/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:30 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/24 15:17:59 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

void	ft_clear_tokenizer(t_list_arg **tokenizer)
{
	t_list_arg *current = *tokenizer;
	t_list_arg *next = *tokenizer;

	while (next != NULL)
	{
		free(current->input_splited);
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
	free(data.signal);
	ft_lst_arg_clear(&data.lst);
	return (0);
}
