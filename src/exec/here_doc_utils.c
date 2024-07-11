/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:34:00 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/11 15:18:36 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 09:19:02 by cyferrei          #+#    #+#             */
/*   Updated: 2024/04/16 15:31:43 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void free_tmp_struct(t_data *data)
{
	//dprintf(2, "SALOPE\n");
    rm_tmp_file(data);
    free(data->tmp_files);
    data->tmp_files = NULL;
}

void	init_tmp_struct(t_data *data)
{
	data->tmp_files = (t_tmp_files *)malloc(sizeof(t_tmp_files));
	if (!data->tmp_files)
		return;
	data->tmp_files->file_name = NULL_INIT;
	data->tmp_files->next = NULL_INIT;
}

void rm_tmp_file(t_data *data)
{
    t_tmp_files *current = data->tmp_files;
    t_tmp_files *next;
	
	// dprintf(2, "SALOPE\n");
    while (current)
    {
		// dprintf(2, "SALOPE\n");
        next = current->next;
		if (current->file_name)
    		unlink(current->file_name);
        free(current->file_name);
        free(current);
        current = next;
    }
    // free(data->tmp_files); // ADD by warren check if cyp ok
	data->tmp_files = NULL;
}

void add_tmp_file(t_data *data, const char *file_name)
{
    t_tmp_files *new_file = (t_tmp_files *)malloc(sizeof(t_tmp_files));
    if (!new_file)
        return;
    new_file->file_name = strdup(file_name);
    new_file->next = data->tmp_files;
    data->tmp_files = new_file;
}
