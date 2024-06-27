/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyferrei <cyferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:48:19 by cyferrei          #+#    #+#             */
/*   Updated: 2024/06/27 15:21:27 by cyferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lib.h"

void	ft_ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = 2;
	// exit 130;
}

void	ft_ctrl_c_children(int sig)
{
	(void)sig;
	g_sig = 2;
	//exit 130
}
void	ft_back_slash(int sig)
{
	(void)sig;
	g_sig = 3;
	// exit 131
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