/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:30 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/03 19:51:27 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"
t_list *parser_init(t_data *data, char **argv)
{
	int i;
	i = ZERO_INIT;
	t_list *tmp = NULL_INIT;
	t_list *save = NULL_INIT;
	data->arg = ft_lstnew(argv[i]);
	save = data->arg;
	tmp = data->arg;
	tmp = tmp->next;
	while(argv[i])
	{
		tmp = ft_lstnew(argv[i]);
		data->arg = tmp;
		tmp = NULL;
		//ft_printf("content of node : %s\n",data->arg->content);//To remove
		data->arg = data->arg->next;
		data->arg = NULL;
		i++;
	}
	return(save);
}

int main(int argc, char **argv, char **envp)
{
    if(argc > 1)
	{
		ft_printf("Too many arguments... exit the program\n");
		exit(EXIT_FAILURE);
	}

	(void)argv;
    t_data data;
	parser_init(&data, envp);
	display_prompt(&data, envp);
	return (0);
}
