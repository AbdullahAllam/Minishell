/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:01:55 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/12 17:58:05 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int code)
{
	(void)code;
	ft_putstr_fd("^C\n", STDERR);
	ft_putstr_fd("\033[0;36m\033[1m😿 minishell ▸ \033[0m", STDERR);
	g_sigf = 1;
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
