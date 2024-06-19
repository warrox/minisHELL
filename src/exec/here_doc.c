/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:21:50 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/18 17:49:04 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	init_here_doc(t_data *data, t_list_arg *tok)
{
	int	fd;
	char *buffer;

	buffer = NULL_INIT;
	fd = ZERO_INIT;
	fd = open(".here_doc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		file_not_found(data, tok);
	while(1)
	{
		write(1, ">", 2);
		if (gnl_hd(0, &buffer) <= 0)
			break;
		if (!buffer || ft_strncmp(tok->file_array[1], buffer, ft_strlen(tok->file_array[1]) + 1) == 0)
		{
			write(fd, "\n", 1);
			break;
		}
		write(fd, buffer, ft_strlen(tok->file_array[1]));
		write(fd, "\n", 1);
		free(buffer);
		close(fd);
		data->exec->infile = open(".here_doc_tmp", O_RDONLY);
		if (data->exec->infile < 0)
		{
			unlink(".here_doc_tmp");
			file_not_found(data, tok);
		}
	}
}