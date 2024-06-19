/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:21:50 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/19 16:28:35 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

// int is_here_doc(t_list_arg *tok)
// {
// 	t_list_arg *tmp;

// 	tmp = tok;
// 	if (!tmp)
// 		return (0);
// 	if (tmp->array_sign[0] == HEREDOCS)
// 		return (1);
// 	return (0);
// }

void	init_here_doc(t_data *data, t_list_arg *tok)
{
	int	fd;
	// char *buffer;

	// buffer = NULL_INIT;
	char *input = NULL_INIT;
	fd = ZERO_INIT;
	fd = open(".here_doc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		file_not_found(data, tok);
	while(1)
	{
		input = readline(">");
		if (!input){
			break;
		}
		// if (gnl_hd(0, &buffer) <= 0)
		// 	break;
		//dprintf(2, "ICI %s\n", tok->file_array[0]);
		if (ft_strncmp(tok->file_array[0], input, ft_strlen(tok->file_array[0]) + 1) == 0)
		{
			// write(fd, "\n", 1);
			break;
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		// free(buffer);
	}
	// free(buffer);
	close(fd);
	data->exec->infile = open(".here_doc_tmp", O_RDONLY);
	if (data->exec->infile < 0)
	{
		unlink(".here_doc_tmp");
		file_not_found(data, tok);
	}
}