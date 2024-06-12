#include "../../includes/minishell_lib.h"
int ft_exit(t_data *data, char *input)
{
	int i = 0;
	char str[4096];
	char s_nbr[4096];
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		
		while(ft_isprint(input[i]))
		{
			i++;
		}
		if(ft_strlen(input) > 4)
		{
			input[i] = 0;
			i = 0;
			int j = 5;
			while(ft_isws(input[j]))
				j++;
			while(input[j] && ft_isdigit(input[j]))
			{
				s_nbr[j] = input[j]; // copie les char digit dans s_nbr 
				j++;
			}
			s_nbr[j] = '\0';
			int nbr = ft_atoi(s_nbr); //convertit le code d'erreur en int
			if(input[j] == '\0')
			{
				return(nbr); // renvoie le int du code erreur
			}
			while(input[i] != '\0')// && !ft_isalnum(input[i]))
			{
				str[i] = input[i];
				i++;
			}
			str[i] = '\0';
			ft_printf("minishell: %s: numeric argument required",str);
		}
		else if(input[i] == '\0')
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

