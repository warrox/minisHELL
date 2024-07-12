/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:48:23 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/11 12:01:33 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	not_valid_identifier(char **split_cmd)
{
	char	*join_1;
	char	*final_join;

	join_1 = NULL;
	final_join = NULL;
	join_1 = ft_strjoin("bash: export: ", split_cmd[0]);
	final_join = ft_strjoin(join_1, ": not a valid identifier\n");
	ft_putstr_fd(final_join, STDERR_FILENO);
	free(join_1);
	free(final_join);
	free_split(split_cmd);
}
