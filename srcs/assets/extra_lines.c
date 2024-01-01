/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 11:54:12 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/01 15:27:44 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extra_lines(int *i, char *c)
{
	*c = ' ';
	(*i)++;
}

void	extra_lines_2(t_minishell *minishell)
{
	minishell->retvalue = 0;
	minishell->exitflag = 1;
}
