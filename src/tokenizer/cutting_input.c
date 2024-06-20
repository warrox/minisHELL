
#include "../../includes/minishell_lib.h"


int	cutting_input(t_data *data, char *input)
{
	int			i;
	char		**split;
	t_list_arg	*new_node;
	i = 0;
	if(checker_err_pipe(input, data) == 0 || check_quote(input, 0, data) == 0) 
		return(-1);
	split = split_pipe_cust(input, '|');
	if (!split)
		return(-1);
	free(data->tokenizer);
	data->tokenizer = ft_lst_cut_new(split[i]);
	i = 1;
	while (split[i])
	{
		new_node = ft_lst_cut_new(split[i]);
		if (new_node)
			ft_lstadd_cut_back(&data->tokenizer, new_node);
		i++;
	}
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return(0);
}
