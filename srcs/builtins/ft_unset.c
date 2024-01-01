/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:00:19 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/01 18:22:21 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_minishell *minishell, t_environement *env)
{
	if (minishell->environment == env && env->next == NULL)
	{
		ft_memdel(minishell->environment->value);
		minishell->environment->value = NULL;
		minishell->environment->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

static size_t	env_length(char *env)
{
	size_t		length;

	length = 0;
	while (env[length] && env[length] != '=')
		length++;
	return (length);
}

int	ft_unset(char **arg, t_minishell *minishell)
{
	t_environement	*env;
	t_environement	*dummy;

	env = minishell->environment;
	if (arg[1] && ft_strncmp(arg[1], env->value, env_length(env->value)) == 0)
	{
		if (env->next)
			minishell->environment = env->next;
		delete_node(minishell, env);
		return (SUCCESS);
	}
	while (env && env->next)
	{
		if (ft_strncmp(arg[1], env->next->value,
				env_length(env->next->value)) == 0)
		{
			dummy = env->next->next;
			delete_node(minishell, env->next);
			env->next = dummy;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}
