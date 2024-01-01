/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:08:47 by ama10362          #+#    #+#             */
/*   Updated: 2023/12/30 17:08:58 by ama10362         ###   ########.fr       */
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
