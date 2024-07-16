/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:13 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 15:10:17 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"
#include <stdio.h>

void	clean_quotes_2(char *str, t_quote *tool_box)
{
	if (tool_box->len > 1)
	{
		if (str[tool_box->start] == '\"' && str[tool_box->end] == '\"'
			&& !tool_box->sf)
		{
			tool_box->df = 1;
			(tool_box->start)++;
			(tool_box->end)--;
		}
		else if (str[tool_box->start] == '\'' && str[tool_box->end] == '\''
			&& !tool_box->df)
		{
			tool_box->sf = 1;
			(tool_box->start)++;
			(tool_box->end)--;
		}
	}
}

void	clean_quote_3(char *str, char **cleaned_str, t_quote *tool_box)
{
	while (tool_box->i <= tool_box->end)
	{
		while (str[tool_box->i] && str[tool_box->i] == '\"' && !tool_box->sf)
			tool_box->i++;
		while (str[tool_box->i] && str[tool_box->i] == '\'' && !tool_box->df)
			tool_box->i++;
		(*cleaned_str)[tool_box->j++] = str[tool_box->i++];
	}
	(*cleaned_str)[tool_box->j] = '\0';
}

char	*clean_quotes(char *str)
{
	char	*cleaned_str;
	t_quote	tool_box;

	init_quote(&tool_box, str);
	clean_quotes_2(str, &tool_box);
	cleaned_str = (char *)malloc((tool_box.end - tool_box.start + 2)
			* sizeof(char));
	if (!cleaned_str)
		return (NULL);
	tool_box.i = tool_box.start;
	tool_box.j = 0;
	clean_quote_3(str, &cleaned_str, &tool_box);
	return (cleaned_str);
}

char	**clean_cmd_array(t_list_arg *tmp, t_data *data)
{
	int		count;
	char	**cleaned_array;

	count = 0;
	while (tmp->tmp_cmd_array && tmp->tmp_cmd_array[count] != NULL)
		count++;
	cleaned_array = (char **)malloc((count + 1) * sizeof(char *));
	if (!cleaned_array)
		return (NULL);
	data->i = 0;
	while (data->i < count)
	{
		cleaned_array[data->i] = clean_quotes(tmp->tmp_cmd_array[data->i]);
		if (!cleaned_array[data->i])
		{
			free_cleaned_array(cleaned_array);
			return (NULL);
		}
		data->i++;
	}
	cleaned_array[count] = NULL;
	return (cleaned_array);
}

int	parse_cmd_arg(t_data *data)
{
	t_list_arg	*tmp;
	int			sort_sign_result;

	tmp = data->tokenizer;
	while (tmp)
	{
		sort_sign_result = sort_sign(tmp, data);
		if (sort_sign_result == -1)
			return (-1);
		else if (sort_sign_result == 0)
			create_signed(tmp);
		tmp->final_cmd = flush_redir(tmp->input_splited, data);
		tmp->tmp_cmd_array = split_tokenizer(tmp, data);
		tmp->cmd_array = clean_cmd_array(tmp, data);
		free_tab_clean(tmp->tmp_cmd_array);
		tmp = tmp->next;
	}
	return (0);
}
