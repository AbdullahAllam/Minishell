/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:56:31 by ama10362          #+#    #+#             */
/*   Updated: 2023/12/30 17:00:30 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initiate_env(t_minishell *minishell, char **env_array)
{
	t_environement	*environment;
	t_environement	*dummy;
	int				i;

	environment = malloc(sizeof(t_environement));
	if (!(environment))
		return (1);
	environment->value = ft_strdup(env_array[0]);
	environment->next = NULL;
	minishell->environment = environment;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		(dummy = malloc(sizeof(t_environement)));
		if (!dummy)
			return (1);
		dummy->value = ft_strdup(env_array[i]);
		dummy->next = NULL;
		environment->next = dummy;
		environment = dummy;
		i++;
	}
	return (0);
}

int	additional_env_init(t_minishell *minishell, char **env_array)
{
	t_environement	*additional_environment;
	t_environement	*dummy;
	int				i;

	additional_environment = malloc(sizeof(t_environement));
	if (!(additional_environment))
		return (1);
	additional_environment->value = ft_strdup(env_array[0]);
	additional_environment->next = NULL;
	minishell->additional_environment = additional_environment;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		(dummy = malloc(sizeof(t_environement)));
		if (!dummy)
			return (1);
		dummy->value = ft_strdup(env_array[i]);
		dummy->next = NULL;
		additional_environment->next = dummy;
		additional_environment = dummy;
		i++;
	}
	return (0);
}
