/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wiring.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:00:06 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/20 02:25:41 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_until(t_minishell *mini, t_token *t)
{
	g_sigf = dup(STDIN);
	close_fd(mini->fdin);
	mini->fdin = open(t->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	ft_putstr_fd('\0', mini->fdin);
	heredoc_loop(mini, t);
	close_fd(mini->fdin);
	mini->fdin = open(t->str, O_RDONLY, S_IRWXU);
	dup2(mini->fdin, STDIN);
	g_sigf = 0;
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

int	pipe_direct(t_minishell *minishell, t_token *token)
{
	pid_t	pid;
	int		pipefd[2];
	t_token	*dummy;

	dummy = token;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		minishell->pipin = pipefd[0];
		dup2(minishell->pipin, STDIN);
		child_job(minishell, pipefd);
		if (next_sep(dummy, NOSKIP) == NULL)
			dup2(minishell->out, STDOUT);
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
		pipe = pipe_direct(mini, token);
	if (of_kind(next, PIPE) && of_kinds(prev, "AT"))
		mixed_seps_case(mini, token);
	if (next && of_kind(next, END) == 0 && pipe != 1)
		brain(mini, next->next);
	if ((of_kind(prev, END) || of_kind(prev, PIPE) || !prev)
		&& pipe != 1 && mini->dont_exec == 0)
		master_exec(mini, token);
}
