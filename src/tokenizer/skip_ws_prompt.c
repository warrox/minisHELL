#include "../../includes/minishell_lib.h"
int skip_ws_prompt(t_data *data, char *input)
{
	data->j = 0;
	while(ft_isws(input[data->j]))			
		data->j++;
	if(input[data->j] == '\0' || input[0] == '\0')
	{
		add_history(input);
		free_prompt(data);
		ft_clear_tokenizer(data);
		return(1);
	}
	return(0);
}	

