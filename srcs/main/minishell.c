/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:41:48 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/12 18:01:53 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigf = 0;

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
