/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:30 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/07 16:38:50 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

void	free_prompt(t_prompt *prompt)
{
	free(prompt->usr_name);
	free(prompt->usr_pwd);
	free(prompt->usr_prompt);
	free(prompt->usr_build_one);
}

void	test(t_data *data)
{
	print_lst(data->lst);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_prompt	cstm_prompt;

	if (argc > 1)
	{
		ft_printf("Too many arguments... exit the program\n");
		exit(EXIT_FAILURE);
	}
	(void)argv;
	parser_list_init(&data, envp);
	// print_lst(data.lst);
	// exit(EXIT_FAILURE);
	display_prompt(&cstm_prompt, envp, &data);
	ft_lst_arg_clear(&data.lst);

	return (0);
}
