/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors_multi_pipe_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:04:13 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 08:10:31 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	error_dir_file_not_found(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(STDERR_FILENO, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
	cleanup_and_exit(data, 1);
}

void	error_is_a_dir_mup(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(STDERR_FILENO, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(STDERR_FILENO, ": Is a directory\n", 17);
	cleanup_and_exit(data, 1);
}

void	error_permission_denied(t_data *data, t_list_arg *tok)
{
	if (tok->cmd_array && tok->cmd_array[0])
		write(STDERR_FILENO, tok->cmd_array[0], ft_strlen(tok->cmd_array[0]));
	write(STDERR_FILENO, ": Permission denied\n", 20);
	cleanup_and_exit(data, 1);
}
