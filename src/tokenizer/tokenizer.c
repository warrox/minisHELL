#include "../../includes/minishell_lib.h"

int check_pipe(char *input, int i,t_data *data)
{
	data->signal->signal = NULL_INIT;
	int flag;
	int flag_s;
	flag = ZERO_INIT;
	flag_s = ZERO_INIT;
	while(input[i])
	{
		if(input[i] == '|')
		{
			if(input[i + 1] == '|')
				break; // to check
			flag += 1;
		}
		i++;
	}
	if(input[i] == '\0' && flag >= 1)
		return(0);
	data->signal->signal = SYNTAX_ERROR; 
	return(1);

}

int checker_err_pipe(char *input,t_data *data)
{
	int i;
	int is_valid;
	int not_valid;
	
	not_valid = 0;
	is_valid = 1;
	i = ZERO_INIT;
	while(input[i])
	{
		if(input[i] == '|')
			break;
		i++;
	}
	if(input[i] == '\0')
		return(is_valid);
	if(check_pipe(input,i,data) == 0) // bloc inverse cense renvoye not valid
		return(is_valid);

	if(data->signal->signal != NULL_INIT)	
		msg_error_handler(&data->signal->signal,data);
	return(not_valid);
}


// ------------------------------------
t_list_arg *ft_lst_cut_new(char *content)
{
    t_list_arg *new_node = (t_list_arg *)malloc(sizeof(t_list_arg));
    if (!new_node)
        return NULL;
    new_node->key_and_val = NULL_INIT;
    new_node->next = NULL_INIT;
    new_node->input_splited = ft_strdup(content);
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

void cutting_input(t_data *data, char *input)
{
    int i = 0;
    char **split;
    t_list_arg *new_node;

	// test split[i] see if it's clean or not.
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

    t_list_arg *tmp = data->tokenizer; // test if the list is well copied. 
    while (tmp)
    {
        ft_printf("res: %s\n", tmp->input_splited);
        tmp = tmp->next;
    }
}

