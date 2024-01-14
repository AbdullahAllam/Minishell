/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wiring.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:00:06 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/12 17:58:00 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_until(t_minishell *mini, t_token *token)
{
	char	*line;
	
	g_sigf = 0;
	close_fd(mini->fdin);
	mini->fdin = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	ft_putstr_fd('\0', mini->fdin);
	while (g_sigf == 0)
	{
		line = readline(">");
		ft_putnbr(g_sigf);
		if (line == NULL || g_sigf == 1)
		{
			free(line);
			close_fd(mini->fdin);
			mini->fdin = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			ft_putstr_fd('\0', mini->fdin);
			break ;
		}
		if (ft_strcmp(line, token->str) == 0)
			g_sigf = 1;
		if (ft_strcmp(line, token->str) != 0 && g_sigf == 0)
			ft_putendl_fd(line, mini->fdin);
		free(line);
	}
	close_fd(mini->fdin);
	mini->fdin = open(token->str, O_RDONLY, S_IRWXU);
	dup2(mini->fdin, STDIN);
}

void	input_direct(t_minishell *mini, t_token *token)
{
	close_fd(mini->fdin);
	mini->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("Shell ERROR: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->retvalue = 1;
		mini->dont_exec = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}

void	out_direct(t_minishell *mini, t_token *token, int type)
{
	close_fd(mini->fdout);
	if (type == TRUNC)
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->fdout == -1)
	{
		ft_putstr_fd("Shell ERROR: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->retvalue = 1;
		mini->dont_exec = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}

int	pipe_direct(t_minishell *minishell)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close_fd(pipefd[1]);
		minishell->pipin = pipefd[0];
		dup2(minishell->pipin, STDIN);
		minishell->pid = -1;
		minishell->parent = 0;
		minishell->dont_exec = 0;
		return (2);
	}
	else
	{
		close_fd(pipefd[0]);
		minishell->pipout = pipefd[1];
		dup2(minishell->pipout, STDOUT);
		minishell->pid = pid;
		minishell->last = 0;
		return (1);
	}
}

void	brain(t_minishell *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (of_kind(prev, TRUNC))
		out_direct(mini, token, TRUNC);
	else if (of_kind(prev, APPEND))
		out_direct(mini, token, APPEND);
	else if (of_kind(prev, INPUT))
		input_direct(mini, token);
	else if (of_kind(prev, DELIM))
		input_until(mini, token);
	else if (of_kind(prev, PIPE))
		pipe = pipe_direct(mini);
	if (next && of_kind(next, END) == 0 && pipe != 1)
		brain(mini, next->next);
	if ((of_kind(prev, END) || of_kind(prev, PIPE) || !prev)
		&& pipe != 1 && mini->dont_exec == 0)
		master_exec(mini, token);
}
