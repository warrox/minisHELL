/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:01:05 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/11 17:23:10 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	create_var_tab(t_data *data, t_list_arg *tmp, int i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	tmp1 = ft_strjoin(tmp->key_and_val[0], "=");
	tmp2 = ft_strjoin(tmp1, tmp->key_and_val[1]);
	free(tmp1);
	data->exec->my_envp[i] = tmp2;
}

void	build_tab_env(t_data *data)
{
	t_list_arg	*tmp;
	int			size;
	int			i;

	tmp = data->lst;
	size = 0;
	i = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	tmp = data->lst;
	data->exec->my_envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!data->exec->my_envp)
		return ;
	while (tmp)
	{
		create_var_tab(data, tmp, i);
		i++;
		tmp = tmp->next;
	}
	data->exec->my_envp[i] = NULL;
}

void	print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->exec->my_envp[i] != NULL)
	{
		printf("%s\n", data->exec->my_envp[i]);
		i++;
	}
}
