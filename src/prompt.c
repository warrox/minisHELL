/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/03 20:09:45 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

static char    *get_pwd(char **envp)
{
    int	i;

	i = ZERO_INIT;
	while (envp[i] && ft_strncmp("PWD", envp[i], 3))
		i++;
	if (ft_strncmp("PWD", envp[i], 3) == 0)
		return (ft_substr(envp[i], 4, ft_strlen(envp[i]) - 4));
	else
		return (NULL);
}

static char    *get_usr(char **envp)
{
    int	i;

	i = ZERO_INIT;
	while (envp[i] && ft_strncmp("USER", envp[i], 4))
		i++;
	if (ft_strncmp("USER", envp[i], 4) == 0)
		return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
	else
		return (NULL);
}

int	display_prompt(t_data *data, char **envp) 
{
    char *input;
	
	input = NULL_INIT;
    while (1) 
	{
        //init_prompt;
        data->usr_name = get_usr(envp);
        data->usr_pwd = get_pwd(envp);
        data->usr_prompt = ft_strjoin(data->usr_name, ":~");
        data->final_usr_prompt = ft_strjoin(data->usr_prompt, data->usr_pwd);
        input = readline(data->final_usr_prompt);
        if (ft_strncmp(input, "exit", 4) == 0) 
		{
            free(input);
            break;
        }
        ft_printf("Vous avez entré: %s\n", input);
        free(input);
    }
    return 0;
}