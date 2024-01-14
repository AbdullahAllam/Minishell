/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kinds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:09:16 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/09 16:00:10 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	of_kind(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

t_token	*find_next(t_token *token, int type, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != type)
		token = token->next;
	return (token);
}

int	of_kinds(t_token *token, char *types)
{
	if (ft_strchr(types, ' ') && of_kind(token, EMPTY))
		return (1);
	else if (ft_strchr(types, 'X') && of_kind(token, CMD))
		return (1);
	else if (ft_strchr(types, 'x') && of_kind(token, ARG))
		return (1);
	else if (ft_strchr(types, 'T') && of_kind(token, TRUNC))
		return (1);
	else if (ft_strchr(types, 'A') && of_kind(token, APPEND))
		return (1);
	else if (ft_strchr(types, 'I') && of_kind(token, INPUT))
		return (1);
	else if (ft_strchr(types, 'D') && of_kind(token, DELIM))
		return (1);
	else if (ft_strchr(types, 'P') && of_kind(token, PIPE))
		return (1);
	else if (ft_strchr(types, 'E') && of_kind(token, END))
		return (1);
	return (0);
}

int	includes_type(t_token *token, int type)
{
	while (token)
	{
		if (of_kind(token, type))
			return (1);
		token = token->next;
	}
	return (0);
}

int	includes_pipe(t_token *token)
{
	while (token && of_kind(token, END) == 0)
	{
		if (of_kind(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}
