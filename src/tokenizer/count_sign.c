/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_sign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:11:19 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 11:16:10 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

bool	is_double_quote(char c)
{
	return (c == '"');
}

int	handle_single_quote(char *ptr, int i)
{
	i++;
	while (ptr[i] && !is_single_quote(ptr[i]))
		i++;
	i++;
	return (i);
}

int	handle_double_quote(char *ptr, int i)
{
	i++;
	while (ptr[i] && !is_double_quote(ptr[i]))
		i++;
	i++;
	return (i);
}

int	handle_sign(char *ptr, int i, int *count)
{
	int	tmp;

	tmp = sign_cmp(&ptr[i]);
	if (tmp != 0)
	{
		(*count)++;
		i += tmp;
	}
	else
		i++;
	return (i);
}

int	count_sign(char *input)
{
	int		count;
	int		i;
	char	*ptr;

	count = 0;
	i = 0;
	ptr = input;
	if (!ptr)
		return (count);
	while (ptr[i])
	{
		if (is_single_quote(ptr[i]))
			i = handle_single_quote(ptr, i);
		else if (is_double_quote(ptr[i]))
			i = handle_double_quote(ptr, i);
		else
			i = handle_sign(ptr, i, &count);
	}
	return (count);
}
