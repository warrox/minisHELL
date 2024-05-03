/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:15:42 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/03 16:15:44 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//PSEUDO CODE NI TESTER NI CORRIGER
#include "../includes/minishell_lib.h"

void parser(char **argv)
{
	t_list_arg *argv_env_var; //variable ex systend_exec_pid
// USELESS	s_list_arg *argv_env_val; // valeur de la variable 1330879
	char **temp; // temporary pour stocker les env_var & env_val avant de les placer dans linked list
	int i;

	argv_env_var = NULL;
	i = 0;
	while(argv[i++])
	{
		temp = ft_split(argv[i],'=');
	}
	while(temp[i])
	{
		argv_env_var->arg_var = temp[i];
		argv_env_var->arg_val = temp[i + 1];
		i+=3; // incremente de 3 en 3 car temp stocke variable et valeur puis on go sur l'element d'apres donc 3 
	}
	//ft_printf()
}
