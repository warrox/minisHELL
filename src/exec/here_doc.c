/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:21:50 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/20 18:42:37 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

char	*build_tmp_file(int idx)
{
	char *tmp_1;
	char *tmp_2;
	char *final;
	
	tmp_1 = NULL_INIT;
	tmp_2 = NULL_INIT;
	final = NULL_INIT;
	tmp_1 = ft_strdup(".here_doc_tmp_");
	tmp_2 = ft_itoa(idx);
	final = ft_strjoin(tmp_1, tmp_2);
	free(tmp_1);
	free(tmp_2);
	return (final);
}

void	is_here_doc(t_data *data, t_list_arg *tok)
{
	int	i;
	static int idx = ZERO_INIT;
	char	*file;
	
	file = NULL_INIT;
	i = 0;
	while (tok->file_array[i])
	{
		if (tok->array_sign[i] == HEREDOCS)
		{
			file = build_tmp_file(idx++);
			init_here_doc(data, tok, i, file);
			tok->array_sign[i] = STDINS;
			free(tok->file_array[i]);
			tok->file_array[i] = ft_strdup(file);
			add_tmp_file(data, file);
			free(file);
			data->exec->here_doc++;
		}
		i++;
	}
}

void	check_here_doc(t_data *data)
{
	t_list_arg *tmp = data->tokenizer;
	char *file;
	
	file = NULL_INIT;
	while(tmp)
	{
		is_here_doc(data, tmp);
		tmp = tmp->next;
	}
}

void	init_here_doc(t_data *data, t_list_arg *tok, int i, char *file)
{
	int	fd;

	char *input = NULL_INIT;
	fd = ZERO_INIT;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		file_not_found(data, tok);
	while(1)
	{
		input = readline(">");
		if (!input){
			break;
		}
		if (ft_strcmp(tok->file_array[i], input) == 0)
			break;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
	}
	close(fd);
}