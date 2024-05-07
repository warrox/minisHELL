/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/07 16:55:48 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

void	free_prompt(t_data *data)
{
	free(data->prompt->usr_name);
	free(data->prompt->usr_pwd);
	free(data->prompt->usr_prompt);
	free(data->prompt->usr_build_one);
	free(data->prompt->usr_build_two);
	free(data->prompt);
}

static char	*get_pwd(char **envp)
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

static char	*get_usr(char **envp)
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

int	display_prompt(t_data *data)
{
	char	*input;
	input = NULL_INIT;
	while (1)
	{
		init_prompt(data);
		build_user_prompt(data);
		input = readline(data->prompt->usr_prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			free_prompt(data);
			break ;
		}
		ft_printf("Vous avez entré: %s\n", input);
		add_history(input);
		input = parser(input, data);
		ft_printf("Resultat: %s\n", input);
		free_prompt(data);
		free(input);
	}
	return (0);
}
