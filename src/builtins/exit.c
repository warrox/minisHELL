#include "../../includes/minishell_lib.h"
long	ft_atoi_long(const char *str)
{
	int		i;
	int		sign;
	long	count;

	i = 0;
	count = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 34
		|| str[i] == 39 || str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		count = (count * 10) + (str[i] - 48);
		i++;
	}
	count = count * sign;
	return (count);
}
int ft_exit(t_data *data, char *input)
{
	int i = 0;
	char str[4096];
	char s_nbr[4096];
	int nbr;

	nbr = 0;
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		
		while(ft_isprint(input[i]))
			i++;
		if(ft_strlen(input) > 4)
		{
			i = 0;
			int j = 3;
			while(!ft_isws(input[j]))
				j++;
			j++;
			while(input[j] && ft_isdigit(input[j]))
			{
				s_nbr[i] = input[j]; // copie les char digit dans s_nbr		
				i++;
				j++;
			}
			s_nbr[j] = '\0';
			nbr = ft_atoi_long(s_nbr); //convertit le code d'erreur en int
			if(input[j] == '\0')
			{
				if(nbr > 2147483646 || nbr < -214730)
				{
					ft_printf("bash: exit: %d: numeric argument required",nbr);
					return(2);
				}
				ft_printf("MODULO : %d\n", nbr % 255);
				return(nbr % 255); // renvoie le int du code erreur
			}
			while(input[i] != '\0')// && !ft_isalnum(input[i]))
			{
				str[i] = input[i];
				i++;
			}
			str[i] = '\0';
			ft_printf("minishell: %s: numeric argument required\n",str);
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
return(256);
}

