/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:38:31 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/17 14:22:29 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_token_alloc(char *line_cmd, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line_cmd[*i + j] && (line_cmd[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line_cmd[*i + j] == '\'' || line_cmd[*i + j] == '\"'))
			c = line_cmd[*i + j++];
		else if (c != ' ' && line_cmd[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line_cmd[*i + j - 1] == '\\')
			count++;
	}
	return (j - count + 1);
}

static t_token	*next_token(char *line_cmd, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = malloc(sizeof(t_token));
	token->str = malloc(sizeof(char) * next_token_alloc(line_cmd, i));
	if (!token || !(token->str))
		return (NULL);
	while (line_cmd[*i] && (line_cmd[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line_cmd[*i] == '\'' || line_cmd[*i] == '\"'))
			c = line_cmd[(*i)++];
		else if (c != ' ' && line_cmd[*i] == c)
			extra_lines(i, &c);
		else if (line_cmd[*i] == '\\' && (*i)++)
			token->str[j++] = line_cmd[(*i)++];
		else
			token->str[j++] = line_cmd[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}

void	classify_type(t_token *token, int sep_neglect)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && sep_neglect == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && sep_neglect == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && sep_neglect == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "<<") == 0 && sep_neglect == 0)
		token->type = DELIM;
	else if (ft_strcmp(token->str, "|") == 0 && sep_neglect == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && sep_neglect == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token	*obtain_tokens(char *line_cmd)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep_neglect;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_neglect_space(line_cmd, &i);
	while (line_cmd[i])
	{
		sep_neglect = neglect_sep(line_cmd, i);
		next = next_token(line_cmd, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		classify_type(next, sep_neglect);
		ft_neglect_space(line_cmd, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

void	arrange_args(t_minishell *minishell)
{
	t_token	*token;
	t_token	*prev;

	token = minishell->first_token;
	while (token)
	{
		prev = prev_sep(token, NOSKIP);
		if (of_kind(token, ARG) && of_kinds(prev, "TAI"))
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev;
			token->next = prev->next;
			prev->next->prev = token;
			prev->next = token;
		}
		token = token->next;
	}
}
