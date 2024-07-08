/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:27:12 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/08 15:02:19 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void print_echo_flag(t_data *data, int start)
{
    int i = start + 1;
    int last = 0;

    // Find the index of the last element
    while (data->tokenizer->cmd_array[last + 1])
        last++;

    // Print the elements
    while (data->tokenizer->cmd_array[i])
    {
        write(data->exec->outfile, data->tokenizer->cmd_array[i], ft_strlen(data->tokenizer->cmd_array[i]));
        if (i < last)
        {
            write(data->exec->outfile, " ", 1);
        }
        i++;
    }
    // write(data->exec->outfile, "\n", 1);
}

void	print_echo(t_data *data, t_list_arg *tok)
{
	int i = 1;
	int flag = 0;
    // dprintf(2, "ICI %d\n", data->exec->outfile);
    // dprintf(2, "ICI %s\n", tok->cmd_array[i]);
	while(tok->cmd_array[flag + 1]){
		// printf("%s",data->tokenizer->cmd_array[i]);
		flag++;	
	}
	while(tok->cmd_array[i])
	{
		flag--;
		write(data->exec->outfile, tok->cmd_array[i], ft_strlen(tok->cmd_array[i]));
		if (flag > 0)
		{
			write(data->exec->outfile, " ", 1);		
		}
		i++;
	}
	write(data->exec->outfile, "\n", 1);
}

int check_flag(t_data *data) {
    int i;
    int j;
    int flag;
    int start;

    start = 0;
    flag = 0;
    i = 0;
    j = 0;
    while (data->tokenizer->cmd_array[i]) {
        j = 0;
        while (data->tokenizer->cmd_array[i][j]) {
            if (data->tokenizer->cmd_array[i][j] == '-') {
                j++;
                // Ensure j is within bounds before further checks
                while (data->tokenizer->cmd_array[i][j] == 'n' && data->tokenizer->cmd_array[i][j] != '\0')
                    j++;
                // Check if current character is a space or null terminator, and ensure it's within bounds
                if (data->tokenizer->cmd_array[i][j] == ' ' || data->tokenizer->cmd_array[i][j] == '\0') {
                    start++;
                } else {
                    break;
                }
            }
            // Ensure j is incremented safely within bounds
            if (data->tokenizer->cmd_array[i][j] != '\0')
                j++;
        }
        i++;
    }
    // dprintf(2, "ICI START %d\n", start);
    return (start);
}


int	check_echo_cmd(t_data *data)
{
	if (ft_strncmp(data->tokenizer->final_cmd, "echo", 5) == 0
		&& data->lst != NULL)
	{
		ft_putstr_fd("\n", data->exec->outfile);
		return (1);
	}
	return (0);
}

int	cmd_echo(t_data *data, t_list_arg *tok)
{
   // dprintf(2, "TESTS\n");
	if (check_echo_cmd(data))
		return (1);
	if (check_flag(data))
	{
		// dprintf(2, "TEST %s\n", data->tokenizer->cmd_array[]);
		// dprintf(2, "%d\n", check_flag(data));
		print_echo_flag(data, check_flag(data));
		return (1);
	}
	if (!check_flag(data))
	{
		print_echo(data, tok);
		return (1);
	}
	return (0);
}
