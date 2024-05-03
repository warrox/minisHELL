#include "minishell_lib.h"

#include <stdio.h>

t_list *parser_init(t_data *data, char **argv)
{
	int i;
	i = 0;
	t_list *tmp;
	t_list *save;
	data->arg = ft_lstnew(argv[i]);
	save = data->arg;
	tmp = data->arg;
	tmp = tmp->next;
	while(argv[i])
	{
		tmp = ft_lstnew(argv[i]);
		data->arg = tmp;
		tmp = NULL;
		data->arg = data->arg->next;
		ft_printf("content of node : %s\n",data->arg->content);
		data->arg = NULL;
		i++;
	}
	return(save);
}
int main(int argc, char **argv, char **envp)
{
    (void)argc;
	(void)argv;
    t_data data;
	parser_init(&data, envp);
	//parser(argv, &data);
    printf("ENV[0]: %s\n", envp[0]);
    return 0;
}
