/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:30 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/03 21:54:34 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"
t_list_arg	*ft_lst_arg_new(void *content)
{
	t_list_arg	*new;

	new = (t_list_arg *)malloc(sizeof(t_list_arg));
	if (!new)
		return (NULL);
	new->full_env_var = content;
	new->key_and_val = NULL_INIT;	
	new->next = NULL;
	return (new);
}
t_list_arg *parser_list_init(t_data *data, char **argv)
{
	int i;
	i = ZERO_INIT;
	t_list_arg *tmp = NULL_INIT;
	t_list_arg *save = NULL_INIT;
	tmp = ft_lst_arg_new(argv[i]);
	save = data->lst;
	tmp = data->lst;
	tmp = tmp->next;
	while(argv[i])
	{
		tmp = ft_lst_arg_new(argv[i]);
		data->lst = tmp;
		tmp = NULL;
		ft_printf("content of node : %s\n",data->lst->full_env_var);//To remove
		data->lst = data->lst->next;
		data->lst = NULL;
		i++;
	}
	return(save);
}
void	parser_key_list(t_data *data)
{
	t_list_arg *tmp = NULL_INIT;
	t_list_arg *save = NULL_INIT;
	save = data->lst;
	while(data->lst)
	{
		tmp->key_and_val = ft_split(data->lst->full_env_var, '=');
		ft_printf("node : %s",tmp->key_and_val[0]);
		data->lst = data->lst->next;
		tmp = tmp->next;
	}
	tmp = save;	
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
	data.lst = parser_list_init(&data, envp);
	//parser_key_list(&data); // segfault dans cette fonction 
	return (0);
}
