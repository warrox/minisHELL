#include "../../includes/minishell_lib.h"
#include <stdio.h>

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

int	ft_isws(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

char	*get_filename(char *str)
{
	int		i;
	int		start;
	int		end;
	char	*new;

	i = 0;
	while (str[i] && ft_isws(str[i]) == 1)
		i++;
	start = i;
	end = i;
	while (str[end] && !ft_isws(str[end]))
		end++;
	if (end == start)
		NULL; // CHECK
	new = ft_substr(str, start, end - start);
	return (new);
}

void	create_signed(t_list_arg *lst)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	lst->file_array = NULL;
	lst->file_array = ft_calloc(lst->count_size + 1, sizeof(char *));
	while (lst->input_splited[i])
	{
		tmp = sign_cmp(&lst->input_splited[i]);
		printf("tmp : %d\n",tmp);
		if(i > 1)
		{
			if(lst->input_splited[i - 1] == '\'')
			tmp = 0;
		}
		if (tmp != 0)
		{
			i += tmp;
			lst->file_array[j++] = get_filename(&lst->input_splited[i]);
		}
		else
			i++;
	}
}
