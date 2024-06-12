#include "../../includes/minishell_lib.h"
int ft_exit(t_data *data, char *input)
{
	int i = 0;
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		ft_printf("TEST : %s\n", input);
		
		while(input[i] != '\0' || input[i] != ' ')
		{
			ft_printf("I : %d\n",i);
			i++;
		}
		if(input[i] == '\0')
		{
			free_prompt(data);
			ft_clear_tokenizer(data);
			free(data->signal);
			if (input)
				free(input);
			return(0);
		}
	}
return(251);
}

