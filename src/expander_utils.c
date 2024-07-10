/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:19:00 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 11:26:44 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_lib.h"

bool isExitCode(char *input, int *i)
{
    return (!ft_strncmp(&input[*i], "$?", 2));
}

bool is_single_quote(char c)
{
    return (c == '\'');
}

bool isVariable(char *input, int *i)
{
    return (!ft_strncmp(&input[*i], "$", 1));
}

char *passTilNextQuote(char *input, int *i, char *buffer, int *j)
{
    (*i)++;  // Pass the opening quote
    while (input[*i] && !is_single_quote(input[*i]))
    {
        buffer[(*j)++] = input[*i];
        (*i)++;
    }
    if (input[*i] == '\'')
    {
        (*i)++;
    }
    buffer[*j] = ' ';
    (*j)++;
    buffer[*j] = '\0'; 
    return buffer;
}

bool isHereDoc(char *input, int *i)
{
    return (!ft_strncmp(&input[*i], "<<", 2));
}


