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
		while(source[i] == ' ' || source[i] == '\t')
			i++;
		copied_s[i] = source[i];
		i++;
	}
	copied_s[i] = '\0';
	return (copied_s);
}
// ------------------------------------
t_list_arg *ft_lst_cut_new(char *content)
{
    t_list_arg *new_node = (t_list_arg *)malloc(sizeof(t_list_arg));
    if (!new_node)
        return NULL;
    new_node->key_and_val = NULL_INIT;
    new_node->next = NULL_INIT;
	if(content[0] == '$')
		new_node->input_splited = ft_strdup_cust(content);
	else
	{
		new_node->input_splited = ft_strdup(content);
	}
    if (!new_node->input_splited)
    {
        free(new_node);
        return NULL;
    }
    return new_node;
}

void ft_lstadd_cut_back(t_list_arg **lst, t_list_arg *new_node)
{
    t_list_arg *tmp;

    if (lst == NULL || new_node == NULL)
        return;

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

void create_signed(t_list_arg *lst) // Tu dois preparer les redirections < > >> | separer la commande et l'argument qui necessitent une redirection du reste de l'input. 
// le probleme ce que tu peux avoir cat > file1 > file2 file 3 file 4
{
	char **result;
	if (lst->redir_sign == STDOUTS)
		result = split_tokenizer(lst->input_splited, '>');
	if (lst->redir_sign == STDINS)
		result = split_tokenizer(lst->input_splited, '<');
	if (lst->redir_sign == HEREDOCS)
		result = split_tokenizer(lst->input_splited, '<');
	if (lst->redir_sign == APPEND)
		result = split_tokenizer(lst->input_splited, '>');
	free(lst->input_splited);
	lst->input_splited = malloc(sizeof(char) * ft_strlen(result[0])+ ft_strlen(result[1])+ 1);
	lst->input_splited = result[0];
	ft_strlcat(lst->input_splited, result[1], (ft_strlen(result[0]) + ft_strlen(result[1])+ 1));
	
}

void  tri_sign(t_list_arg *tmp) // secure les if || sert a trouver les signes dans le splitted input.
{
	int i = 0;
	ft_printf("inside the string : %s\n",tmp->input_splited);
	while(tmp->input_splited[i])
	{
		if(tmp->input_splited[i] == '<' && tmp->input_splited[i + 1] != '<')
		{
			tmp->redir_sign = STDINS;
		}
		if(tmp->input_splited[i] == '>' && tmp->input_splited[i + 1] != '>' )
		{
			tmp->redir_sign = STDOUTS;
		}
		if(tmp->input_splited[i] == '>' && tmp->input_splited[i + 1] == '>')
		{
			ft_printf("Go A\n");
			tmp->redir_sign = APPEND;
		}
		if(tmp->input_splited[i] == '<' && tmp->input_splited[i + 1] == '<')
		{
			ft_printf("Go B\n");
			tmp->redir_sign = HEREDOCS;
			ft_printf("SIGN : %d\n",tmp->redir_sign);
		}
		i++;
	}
	
}
void parse_cmd_arg(t_data *data)
{
	data->tokenizer->redir_sign = ZERO_INIT;
	t_list_arg *tmp = data->tokenizer;
	while(tmp)
	{
		tri_sign(tmp);
		if(tmp->redir_sign != ZERO_INIT)
		{
			ft_printf("NOT OK \n");
			create_signed(tmp);
			tmp->cmd_and_arg = ft_split(tmp->input_splited, ' ');
		}
		else
		{
			ft_printf("OK\n");
			tmp->cmd_and_arg = ft_split(tmp->input_splited, ' ');
		}
		tmp = tmp->next;
	}
}


void cutting_input(t_data *data, char *input)
{
    int i = 0;
    char **split;
    t_list_arg *new_node;

	checker_err_pipe(input,data);
    split = ft_split(input, '|');
    if (!split)
		return;	
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
//redir =  

