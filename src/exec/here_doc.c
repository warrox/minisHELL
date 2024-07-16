/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:21:50 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 08:09:06 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

char	*build_tmp_file(int idx)
{
	char	*tmp_1;
	char	*tmp_2;
	char	*final;

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
	int			i;
	static int	idx = ZERO_INIT;
	char		*file;

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
	t_list_arg	*tmp;

	tmp = data->tokenizer;
	while (tmp)
	{
		is_here_doc(data, tmp);
		tmp = tmp->next;
	}
}
int		g_sig;

int	helper_init_hd(int g_sig, t_data *data, t_list_arg *tok, int i)
{
	if (!data->input_hd && g_sig != 2)
	{
		data->exec->ctrl_heredoc = 2;
		data->join = ft_strjoin("minishell: warning: here-document \
		at line 1 delimited by end-of-file (wanted `",
				tok->file_array[i]);
		data->join_2 = ft_strjoin(data->join, "')\n");
		ft_putstr_fd(data->join_2, STDERR_FILENO);
		free(data->join);
		free(data->join_2);
		return (-1);
	}
	else if (g_sig == 2)
	{
		data->exec->ctrl_heredoc = 1;
		write(1, "^C\n", 3);
		data->spe_fd = open("/dev/tty", O_RDONLY);
		close(data->tmp_files->fd);
		return (-1);
	}
	return (0);
}

void	init_here_doc(t_data *data, t_list_arg *tok, int i, char *file)
{
	data->spe_fd = ZERO_INIT;
	data->input_hd = NULL_INIT;
	data->tmp_files->fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->tmp_files->fd < 0)
		file_not_found(data, tok);
	if (data->exec->ctrl_heredoc == 1)
	{
		close(data->tmp_files->fd);
		return ;
	}
	while (1)
	{
		g_sig = 0;
		handle_signal_here_doc();
		data->input_hd = readline(">");
		if (helper_init_hd(g_sig, data, tok, i) == -1)
			break ;
		if (ft_strcmp(tok->file_array[i], data->input_hd) == 0)
			break ;
		write(data->tmp_files->fd, data->input_hd, ft_strlen(data->input_hd));
		write(data->tmp_files->fd, "\n", 1);
	}
	close(data->tmp_files->fd);
}
