/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:07:06 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/09 11:07:49 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell_lib.h"


void init_check_quote(int *i, int *first_enter, int *flag_s, int *flag_d, int *signal)
{
    (*i) = 0;
    (*flag_s) = 0;
    (*flag_d) = 0;
    (*first_enter) = 0;
    (*signal) = 0;
}

