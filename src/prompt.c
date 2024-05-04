/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:17:55 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/04 18:48:27 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

static void	init_prompt(t_prompt *prompt)
{
	prompt->usr_name = NULL_INIT;
	prompt->usr_pwd = NULL_INIT;
	prompt->usr_build_one = NULL_INIT;
	prompt->usr_prompt = NULL_INIT;
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

int	display_prompt(t_prompt *prompt, char **envp)
{
	char	*input;

	input = NULL_INIT;
	while (1)
	{
		init_prompt(prompt);
		prompt->usr_name = get_usr(envp);
		prompt->usr_pwd = get_pwd(envp);
		prompt->usr_build_one = ft_strjoin(prompt->usr_name, ":~");
		prompt->usr_prompt = ft_strjoin(prompt->usr_build_one, prompt->usr_pwd);
		input = readline(prompt->usr_prompt);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			free_prompt(prompt);
			break ;
		}
		ft_printf("Vous avez entré: %s\n", input);
		free_prompt(prompt);
		free(input);
	}
	return (0);
}
