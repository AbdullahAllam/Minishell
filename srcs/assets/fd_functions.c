/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:08:47 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/09 01:29:17 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initiate_fds(t_minishell *minishell)
{
	minishell->fdin = -1;
	minishell->fdout = -1;
	minishell->pipin = -1;
	minishell->pipout = -1;
	minishell->pid = -1;
}

void	close_fd(int fd)
{
	if (fd > 0)
		close(fd);
}

void	close_2_fds(int fd1, int fd2)
{
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
}

void	close_fds(t_minishell *minishell)
{
	close_fd(minishell->fdin);
	close_fd(minishell->fdout);
	close_fd(minishell->pipin);
	close_fd(minishell->pipout);
}

void	reset_std(t_minishell *minishell)
{
	dup2(minishell->input, STDIN);
	dup2(minishell->out, STDOUT);
}
