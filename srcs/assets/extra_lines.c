/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 11:54:12 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/06 22:23:22 by ama10362         ###   ########.fr       */
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

int	extra_lines_3(int ret)
{
	if (ret == 32256 || ret == 32512)
		ret = ret / 256;
	else
		ret = !!ret;
	return (ret);
}

void	extra_lines_4(t_minishell *minishell, t_token *token)
{
	if (of_kinds(minishell->first_token, "TAI"))
	{
		token = minishell->first_token->next;
	}
	else
		token = token;
}

int	extra_lines_5(t_minishell *minishell, int status)
{
	int	retvalue;

	if (minishell->last == 0)
		retvalue = status;
	else
		retvalue = minishell->retvalue;
	return (retvalue);
}
