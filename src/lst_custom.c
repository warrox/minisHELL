
#include "../includes/minishell_lib.h"


void	ft_lstadd_arg_back(t_list_arg **lst, t_list_arg *new)
{
	t_list_arg	*tmp;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = ft_lst_arg_last((*lst));
			tmp->next = new;
		}
	}
}
t_list_arg	*ft_lst_arg_new(t_list_arg *new,char *content)
{

	new = (t_list_arg *)malloc(sizeof(t_list_arg));
	if (!new)
		return (NULL);
	new->key_and_val = NULL_INIT;	
	new->next = NULL_INIT;
	new->key_and_val = ft_split(content, '=');
	return (new);
}
void parser_list_init(t_data *data, char **envp)
{
	int i;
	i = ZERO_INIT;
	while(envp[i])
	{
		ft_lstadd_arg_back(&data->lst,ft_lst_arg_new(data->lst,envp[i]));
		i++;
	}
}

void print_lst(t_list_arg *lst)
{
	while(lst)
	{
		ft_printf("{Key[0] : %s}\n", lst->key_and_val[0]);
		ft_printf("{Value[1] : %s}\n", lst->key_and_val[1]);
		lst = lst->next;
	}
}
