/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:47:46 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/05 16:59:16 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initiate_shell(t_minishell *minishell)
{
	minishell->exitflag = 0;
	minishell->retvalue = 0;
	minishell->dont_exec = 0;
	minishell->first_token = NULL;
	minishell->input = dup(STDIN);
	minishell->out = dup(STDOUT);
}
