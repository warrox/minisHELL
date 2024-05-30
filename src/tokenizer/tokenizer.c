/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:37:13 by cyferrei          #+#    #+#             */
/*   Updated: 2024/05/30 10:52:34 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

char	*ft_strdup_cust(const char *source)
{
	int		i;
	char	*copied_s;

	i = 0;
	copied_s = malloc(ft_strlen(source) + 1);
	if (!copied_s)
		return (NULL);
	while (source[i])
	{
		while (source[i] == ' ' || source[i] == '\t')
			i++;
		copied_s[i] = source[i];
		i++;
	}
	copied_s[i] = '\0';
	return (copied_s);
}
// ------------------------------------

int sign_cmp(char *str)
{
	if (strncmp(str, ">>", 2) == 0)
		return 2;
	else if (ft_strncmp(str, "<<", 2) == 0)
		return 2;
	else if (ft_strncmp(str, ">", 1) == 0)
		return 1;
	else if (ft_strncmp(str, "<", 1) == 0)
		return 1;
	return 0;
}

int	count_sign(char *input)
{
	int	count;
	int tmp;
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		tmp = sign_cmp(&input[i]);
		if (tmp != 0)
		{
			count++;
			i += tmp;
		}
		else
			i++;
	}
	return (count);
}
t_list_arg	*ft_lst_cut_new(char *content)
{
	t_list_arg	*new_node;

	new_node = (t_list_arg *)malloc(sizeof(t_list_arg));
	if (!new_node)
		return (NULL);
	new_node->key_and_val = NULL_INIT;
	new_node->next = NULL_INIT;
	if (content[0] == '$')
		new_node->input_splited = ft_strdup_cust(content);
	else
	{
		new_node->input_splited = ft_strdup(content);
	}
	if (!new_node->input_splited)
	{
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	ft_lstadd_cut_back(t_list_arg **lst, t_list_arg *new_node)
{
	t_list_arg	*tmp;

	if (lst == NULL || new_node == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

int ft_isws(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

char *get_filename(char *str)
{
	int i = 0;
	int start;
	int end;
	char *new;
	while (str[i] && ft_isws(str[i]) == 1)
		i++;
	start = i;
	end = i;
	while (str[end] && !ft_isws(str[end]))
		end++;
	if (end == start)
		NULL; //CHECK
	new = ft_substr(str, start, end - start);
	return new;
}

void	create_signed(t_list_arg *lst)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	lst->file_array = NULL;
	lst->file_array = ft_calloc(lst->count_size + 1, sizeof(char *));
	while (lst->input_splited[i])
	{
		tmp = sign_cmp(&lst->input_splited[i]);
		if (tmp != 0)
		{
			i += tmp;
			lst->file_array[j++] = get_filename(&lst->input_splited[i]);
		}
		else
			i++;
	}
}

void	sort_sign(t_list_arg *tmp) // secure les if || sert a trouver les signes dans le splitted input.
{
	int i = 0;
	int j = 0;
	// ft_printf("inside the string : %s\n",tmp->input_splited);
	tmp->count_size = count_sign(tmp->input_splited);
	ft_printf("valeur de count sign : %d\n",tmp->count_size);
	i = 0;
	tmp->array_sign = ft_calloc(tmp->count_size + 1, sizeof(int));
	while (tmp->count_size && tmp->input_splited[i])
	{
		if (ft_strncmp(&tmp->input_splited[i], "<<", 2) == 0)
		{
			tmp->array_sign[j++] = HEREDOCS;
			i += 2;
		}
		else if (ft_strncmp(&tmp->input_splited[i], ">>", 2) == 0)
		{
			tmp->array_sign[j++] = APPEND;
			i += 2;
		}
		else if (ft_strncmp(&tmp->input_splited[i], "<", 1) == 0)
		{
			tmp->array_sign[j++] = STDINS;
			i += 1;
		}
		else if (ft_strncmp(&tmp->input_splited[i], ">", 1) == 0)
		{
			tmp->array_sign[j++] = STDOUTS;
			i += 1;
		}
		else
			i++;
	}
}

int get_word_size(char *str)
{
	int i = 0;
	while (str[i] && ft_isws(str[i]))
		i++;
	while (str[i] && !ft_isws(str[i]))
		i++;
	return i;
}

char *flush_redir(char *str)
{
	char buffer[2048];
	int i = 0;
	int tmp = 0;
	int j = 0;
	while (str[i])
	{
		tmp = sign_cmp(&str[i]);
		if (tmp)
		{
			i += tmp;
			i += get_word_size(&str[i]);
		}
		else {
			buffer[j++] = str[i];
			i++;
		}
	}
	buffer[j] = 0;
	return (ft_strdup(buffer));
}

void	parse_cmd_arg(t_data *data)
{
	t_list_arg	*tmp;
	
	tmp = data->tokenizer;
	while (tmp)
	{
		sort_sign(tmp);
		create_signed(tmp);
		tmp->final_cmd = flush_redir(tmp->input_splited);
		tmp = tmp->next;
	}
}

void	cutting_input(t_data *data, char *input)
{
	int			i;
	char		**split;
	t_list_arg	*new_node;

	i = 0;
	checker_err_pipe(input, data);
	split = ft_split(input, '|'); //po bon
	if (!split)
		return ;
	free(data->tokenizer);
	data->tokenizer = ft_lst_cut_new(split[i]);
	i = 1;
	while (split[i])
	{
		new_node = ft_lst_cut_new(split[i]);
		if (new_node)
		{
			ft_lstadd_cut_back(&data->tokenizer, new_node);
		}
		i++;
	}
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	// ft_printf("data->tokenizer = %p\n", data->tokenizer);
	// print_lst_token(data->tokenizer);
}

// input > premier decoupage |
// second tour > $expand
// third > char **cmd_and_arg pour les commandes
// cat > < >>
// cat file1 > file2 > file10 > file x
// redir =
