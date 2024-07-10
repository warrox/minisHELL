/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:07:06 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/10 18:28:44 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell_lib.h"

void	init_check_quote(int *first_enter,
		int *signal, t_data *data)
{
	data->i = 0;
	data->flag_s = 0;
	data->flag_d = 0;
	(*first_enter) = 0;
	(*signal) = 0;
}
