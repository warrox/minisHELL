/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:48:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/07/16 07:15:53 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

extern int	g_sig;

void	ft_ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_sig = 2;
}

void	ft_ctrl_c_children(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	g_sig = 2;
}

void	handle_signal_here_doc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c_here_doc);
}

void	handle_signal_children(void)
{
	signal(SIGQUIT, ft_back_slash);
	signal(SIGINT, ft_ctrl_c_children);
}

void	handle_signal_prompt(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c);
}
