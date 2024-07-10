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
	char *nbr_char;
	int neg = 1;
	int	quote = 0;
	char **tmp = data->tokenizer->cmd_array;

	ft_bzero(s_nbr,4096);
	nbr = 0;
	int count = 0;
	while (tmp[i])
	{
		count++;
		i++;
	}
	i = 0;
	if (count > 2)
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		data->exit_status = 1;
		exit (data->exit_status);
	}
	if (ft_strncmp(input, "exit", 4) == 0)
	{
		while(ft_isprint(input[i]))
			i++;
		if(ft_strlen(input) > 4)
		{
			i = 0;
			int j = 3;
			while(input[j] && !ft_isws(input[j]))
				j++;
			j++;
			if(input[j] == '+' || input[j] == '-')
			{
				if (input[j] == '-')
					neg = - neg;
				j++;
			}
			if (input[j] == '"')
			{
				quote = 1;
				j++;
			}
			if(input[j] == '+' || input[j] == '-')
			{
				if (input[j] == '-')
					neg = - neg;
				j++;
			}
			while(input[j] && ft_isdigit(input[j]))
			{
				s_nbr[i] = input[j];	
				i++;
				j++;
			}
			s_nbr[j] = '\0';
			nbr = ft_atoi_long(s_nbr);
			if (neg == -1)
				nbr = -nbr;
			nbr_char = ft_itoa((int)nbr);
			if (neg == -1)
			{
				if (ft_strncmp(data->tokenizer->cmd_array[1], nbr_char, ft_strlen(data->tokenizer->cmd_array[1])) != 0)
				{
					data->exit_status = nbr % 256;
					free(nbr_char);
					free_prompt(data);
					free(data->signal);
					free_exec(data);
					free_tmp_struct(data);
					ft_lst_arg_clear(&data->lst);
					ft_clear_tokenizer(data);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				if (ft_strncmp(s_nbr, nbr_char, ft_strlen(s_nbr)) != 0)
				{
					data->exit_status = nbr % 256;
					free(nbr_char);
					free_prompt(data);
					free(data->signal);
					free_exec(data);
					free_tmp_struct(data);
					ft_lst_arg_clear(&data->lst);
					ft_clear_tokenizer(data);
					exit(EXIT_FAILURE);
				}
			}
			if(input[j] == '\0')
			{
				// if(nbr > 2147483647 || nbr < -2147483648)
				// {
				// 	data->exit_status = nbr;
				// 	return(2);
				// }
				free(nbr_char);
				free_prompt(data);
				free(data->signal);
				free_exec(data);
				free_tmp_struct(data);
				ft_lst_arg_clear(&data->lst);
				ft_clear_tokenizer(data);
				//dprintf(2, "SALOPE\n");
				data->exit_status = nbr % 256;
				exit(data->exit_status);
			}
			while(input[i] != '\0')
			{
				str[i] = input[i];
				i++;
			}
			str[i] = '\0';
			if (quote)
			{
				data->exit_status = nbr % 256;
				free(nbr_char);
				free_prompt(data);
				free(data->signal);
				free_exec(data);
				free_tmp_struct(data);
				ft_lst_arg_clear(&data->lst);
				ft_clear_tokenizer(data);
				exit (data->exit_status);
			}
			else
			{
				ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
				data->exit_status = 2;
				exit (data->exit_status);
			}
		}
		else if(input[i] == '\0')
		{
			free_prompt(data);
			free(data->signal);
			free_exec(data);
			free_tmp_struct(data);
			ft_lst_arg_clear(&data->lst);
			ft_clear_tokenizer(data);
			exit(0);
		}
	}
	return(256);
}

