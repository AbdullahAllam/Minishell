/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:41:48 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/20 02:25:50 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigf = 0;

void	mixed_seps_case(t_minishell *mini, t_token *token)
{
	master_exec(mini, previous(token, SKIP));
	mini->childroute = 1;
}

void	child_job(t_minishell *minishell, int *pipefd)
{
	minishell->pid = -1;
	minishell->parent = 0;
	minishell->dont_exec = 0;
	close_fd(pipefd[1]);
}

void	heredoc_loop(t_minishell *mini, t_token *t)
{
	char	*line;

	while (1)
	{
		if (g_sigf != -1)
			ft_putstr("> ");
		line = get_next_line(g_sigf);
		if (line == NULL || g_sigf == -1)
		{
			close_fd(mini->fdin);
			mini->fdin = open(t->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			ft_putstr_fd('\0', mini->fdin);
			break ;
		}
		if (ft_strcmp(line, t->str) == 10)
			break ;
		if (ft_strcmp(line, t->str) != 10 && g_sigf != -1)
			ft_putstr_fd(line, mini->fdin);
	}
	free(line);
}

void	myshell(t_minishell *minishell)
{
	t_token	*token;
	int		status;

	token = next(minishell->first_token, NOSKIP);
	extra_lines_4(minishell, token);
	while (minishell->exitflag == 0 && token)
	{
		minishell->childroute = 1;
		minishell->parent = 1;
		minishell->last = 1;
		brain(minishell, token);
		reset_std(minishell);
		close_fds(minishell);
		initiate_fds(minishell);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		minishell->retvalue = extra_lines_5(minishell, status);
		if (minishell->parent == 0)
		{
			clean_token(minishell->first_token);
			exit(minishell->retvalue);
		}
		minishell->dont_exec = 0;
		token = next(token, SKIP);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	initiate_shell(&minishell);
	initiate_fds(&minishell);
	initiate_env(&minishell, env);
	additional_env_init(&minishell, env);
	increase_shlvl(minishell.environment);
	while (minishell.exitflag == 0)
	{
		parse_line(&minishell);
		if (minishell.first_token != NULL
			&& validate_line(&minishell, minishell.first_token))
			myshell(&minishell);
		clean_token(minishell.first_token);
		minishell.first_token = NULL;
	}
	rl_clear_history();
	clean_environment(minishell.environment);
	clean_environment(minishell.additional_environment);
	return (minishell.retvalue);
}
