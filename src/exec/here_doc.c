/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:21:50 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/15 15:00:55 by cyferrei         ###   ########.fr       */
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
int g_sig;

void	init_here_doc(t_data *data, t_list_arg *tok, int i, char *file)
{
	char	*input;
	char	*join;
	char	*join_2;
	data->spe_fd = ZERO_INIT;
	input = NULL_INIT;
	data->tmp_files->fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dprintf (2, "FILE %s\n", file);
	if (data->tmp_files->fd < 0) {
		dprintf(2, "PD VA\n");
		file_not_found(data, tok);
	}
	//dprintf(2, "ctrl_hd = %d\n", data->exec->ctrl_heredoc);
	if (data->exec->ctrl_heredoc == 1)
	{
		close(data->tmp_files->fd);
		return;
	}
	while (1)
	{
		g_sig = 0;
		handle_signal_here_doc();
		input = readline(">");
		if (!input && g_sig != 2) 
		{
			data->exec->ctrl_heredoc = 2;
			join = ft_strjoin("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `", tok->file_array[i]);
			join_2 = ft_strjoin(join, "')\n");
			ft_putstr_fd(join_2, STDERR_FILENO);
			free(join);
			free(join_2);
			break ;
		} 
		else if(g_sig == 2)
		{
			//dprintf(2, "ICI %d\n", g_sig);
			data->exec->ctrl_heredoc = 1;
			write(1, "^C\n", 3);
			data->spe_fd = open("/dev/tty", O_RDONLY);
			close(data->tmp_files->fd);
			break;
			//n'execute pas la commande ni les autres here_doc
		}
		if (ft_strcmp(tok->file_array[i], input) == 0)
			break ;
		write(data->tmp_files->fd, input, ft_strlen(input));
		write(data->tmp_files->fd, "\n", 1);
	}
	close(data->tmp_files->fd);
}
