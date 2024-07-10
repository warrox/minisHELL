/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_cust_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:45:23 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 15:54:32 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	s_pipe_init(t_tool *tool)
{
	tool->len = 0;
	tool->temp = NULL;
	tool->temp_ptr = NULL;
}

void	token_ws(char **token_start, char **token_end)
{
	while (*token_start < *token_end && (**token_start == ' '
			|| **token_start == '\t'))
		token_start++;
}
