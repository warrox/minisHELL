/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:11:44 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 12:39:26 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

bool	redirsign(char c)
{
	return (c == '<' || c == '>');
}

int	ft_isws(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

char	*gn(char *str, t_tool *tool)
{
	int		start;
	char	*new;

	while (str[tool->ii] && ft_isws(str[tool->ii]))
		tool->ii++;
	start = tool->ii;
	if (str[start] == '\"' || str[start] == '\'')
	{
		start++;
		tool->dq = !tool->dq;
	}
	tool->end = tool->ii;
	while (str[tool->end] && (!ft_isws(str[tool->end]) || (tool->dq
				&& !is_double_quote(str[tool->end]))))
		tool->end++;
	if (tool->end == start)
		NULL;
	if (str[tool->end - 1] == '\"' || str[tool->end - 1] == '\'')
		tool->end--;
	new = ft_substr(str, start, tool->end - start);
	return (new);
}

void	init_tool(t_tool *tool, t_list_arg *lst)
{
	tool->i = 0;
	tool->j = 0;
	tool->ii = 0;
	tool->tmp = 0;
	lst->file_array = NULL;
}

void	create_signed(t_list_arg *lst)
{
	t_tool	tool;

	init_tool(&tool, lst);
	lst->file_array = ft_calloc(lst->count_size + 1, sizeof(char *));
	while (lst->input_splited[tool.i])
	{
		tool.tmp = sign_cmp(&lst->input_splited[tool.i]);
		if (tool.i > 1)
		{
			if (lst->input_splited[tool.i - 1] == '\'')
				tool.tmp = 0;
		}
		if (&lst->input_splited[tool.i] && tool.tmp != 0)
		{
			tool.i += tool.tmp;
			if (lst->count_size != 0)
			{
				lst->file_array[tool.j++] = gn(&lst->input_splited[tool.i],
						&tool);
				lst->count_size--;
			}
		}
		else
			tool.i++;
	}
}
