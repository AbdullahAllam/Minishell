/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:01:55 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/19 23:59:56 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int code)
{
	(void)code;
	if (g_sigf == 0)
	{
		write(STDERR, "^C\n", 3);
		rl_on_new_line();
		ft_putstr_fd("😿 ", STDERR);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_sigf == 2)
		ft_putstr_fd("^C\n", STDERR);
	else
	{
		close_fd(g_sigf);
		ft_putstr_fd("^C\n", STDERR);
		g_sigf = -1;
	}
}

void	sig_quit(int code)
{
	(void)code;
}

void	signals_handle(void)
{
	struct termios	termios_new;

	tcgetattr(0, &termios_new);
	termios_new.c_lflag &= ~0001000;
	tcsetattr(0, 0, &termios_new);
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, &sig_int);
}
