/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:41:48 by ama10362          #+#    #+#             */
/*   Updated: 2023/12/30 16:54:52 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			//minishell(&minishell);
		clean_token(minishell.first_token);
		minishell.first_token = NULL;
	}
	rl_clear_history();
	clean_environment(minishell.environment);
	clean_environment(minishell.additional_environment);
	return (minishell.retvalue);
}
