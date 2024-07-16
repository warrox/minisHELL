/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 07:11:36 by whamdi            #+#    #+#             */
/*   Updated: 2024/07/16 07:15:51 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	ft_ctrl_c_here_doc(int sig)
{
	(void)sig;
	g_sig = 2;
	close(STDIN_FILENO);
}

void	ft_back_slash(int sig)
{
	(void)sig;
	g_sig = 3;
}
