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

t_list_arg *create_signed(t_data *data, int i) // Tu dois preparer les redirections < > >> | separer la commande et l'argument qui necessitent une redirection du reste de l'input. 
// le probleme ce que tu peux avoir cat > file1 > file2 file 3 file 4
{
	//if
	//data->sign_to_exe = ft_lstnew(cmd_and_arg[1]);
	(void) i;
	return(data->tokenizer);	
}

void  tri_sign(t_data *data) // secure les if || sert a trouver les signes dans le splitted input.
{
	int i = 0;
	t_list_arg *tmp;
	tmp = data->tokenizer;
	while(tmp) 
	{
		while(tmp->input_splited[i])
		{
			if(tmp->input_splited[i] == '<' && tmp->input_splited[i + 1] != '<')
			{
				tmp->redir_sign = STDINS;
			}
			if(tmp->input_splited[i] == '>')
			{
				tmp->redir_sign = STDOUTS;
			}
			if(tmp->input_splited[i] == '>' && tmp->input_splited[i + 1] == '>')
			{
				tmp->redir_sign = HEREDOCS;
			}
			i++;
		}
		tmp = tmp->next;
	}
	
}
void parse_cmd_arg(t_data *data)
{
	data->tokenizer->redir_sign = ZERO_INIT;
	t_list_arg *tmp = data->tokenizer;
	while(tmp)
	{
		tri_sign(data);
		// ft_printf("go\n");
		if(tmp->redir_sign != ZERO_INIT)
		{
			ft_printf("NOT OK \n");
			//create_signed(data, 0); // ici tu geres si il y'a une redirection
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

