/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:10:21 by ama10362          #+#    #+#             */
/*   Updated: 2023/12/30 17:37:07 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_q(char *line_cmd, int length)
{
	int	i;
	int	open_quotes;

	i = 0;
	open_quotes = 0;
	while (line_cmd[i] && i != length)
	{
		if (i > 0 && line_cmd[i - 1] == '\\')
			;
		else if (open_quotes == 0 && line_cmd[i] == '\"')
			open_quotes = 1;
		else if (open_quotes == 0 && line_cmd[i] == '\'')
			open_quotes = 2;
		else if (open_quotes == 1 && line_cmd[i] == '\"')
			open_quotes = 0;
		else if (open_quotes == 2 && line_cmd[i] == '\'')
			open_quotes = 0;
		i++;
	}
	return (open_quotes);
}

int	is_separating(char *line_cmd, int i)
{
	if (i > 0 && line_cmd[i - 1] == '\\' && ft_strchr("<>|;", line_cmd[i]))
		return (0);
	else if (ft_strchr("<>|;", line_cmd[i]) && check_q(line_cmd, i) == 0)
		return (1);
	else
		return (0);
}

int	neglect_sep(char *line_cmd, int i)
{
	if (line_cmd[i] && line_cmd[i] == '\\'
		&& line_cmd[i + 1] && line_cmd[i + 1] == ';')
		return (1);
	else if (line_cmd[i] && line_cmd[i] == '\\'
		&& line_cmd[i + 1] && line_cmd[i + 1] == '|')
		return (1);
	else if (line_cmd[i] && line_cmd[i] == '\\'
		&& line_cmd[i + 1] && line_cmd[i + 1] == '>')
		return (1);
	else if (line_cmd[i] && line_cmd[i] == '\\'
		&& line_cmd[i + 1] && line_cmd[i + 1] == '>'
		&& line_cmd[i + 2] && line_cmd[i + 2] == '>')
		return (1);
	return (0);
}

int	validate_line(t_minishell *minishell, t_token *token)
{
	while (token)
	{
		if (of_kinds(token, "TAI")
			&& (!token->next || of_kinds(token->next, "TAIPE")))
		{
			ft_putendl_fd("Shell: error near unexpected token ", STDERR);
			minishell->retvalue = 258;
			return (0);
		}
		if (of_kinds(token, "PE")
			&& (!token->prev || !token->next || of_kinds(token->prev, "TAIPE")))
		{
			ft_putendl_fd("Shell: error near unexpected token ", STDERR);
			minishell->retvalue = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

int	is_last_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || of_kind(token, CMD) || of_kind(token, ARG))
	{
		prev = prev_sep(token, NOSKIP);
		if (!prev || of_kind(prev, END) || of_kind(prev, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}
