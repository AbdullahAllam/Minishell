/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:46:25 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/01 15:25:35 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_minishell *minishell, char **args)
{
	ft_putstr_fd("exit 😽\n", STDERR);
	if (args[1])
	{
		if (!ft_strisnum(args[1]))
		{
			minishell->retvalue = 1;
			minishell->exitflag = 1;
			ft_putendl_fd("Shell: Numeric Arguments Required", STDERR);
		}
		else if (args[2])
		{
			minishell->retvalue = 1;
			minishell->exitflag = 0;
			ft_putendl_fd("Shell: Too many Arguments", STDERR);
		}
		else
			extra_lines_2(minishell);
	}
	else
		extra_lines_2(minishell);
}
