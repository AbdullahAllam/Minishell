/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obtain_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:00:42 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/09 01:41:29 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	legal_env(const char *env)
{
	int		i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}

int	legal_char(int c)
{
	if (ft_isalnum(c) == 1)
		return (1);
	return (0);
}

static int	environment_value_len(const char *env_value)
{
	int		i;
	int		value_size;

	value_size = 0;
	i = 0;
	while (env_value[i] && env_value[i] != '=')
		i++;
	i += 1;
	while (env_value[i])
	{
		i++;
		value_size++;
	}
	return (value_size);
}

char	*environment_value(char *env_value)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*environemnt_val;

	size_alloc = environment_value_len(env_value) + 1;
	environemnt_val = malloc(sizeof(char) * size_alloc);
	if (!environemnt_val)
		return (NULL);
	i = 0;
	while (env_value[i] && env_value[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env_value[i])
		environemnt_val[j++] = env_value[i++];
	environemnt_val[j] = '\0';
	return (environemnt_val);
}

char	*obtain_value(char *arg, t_environement *env)
{
	char	environemnt_name[BUFF_SIZE];
	char	*environemnt_val;

	environemnt_val = ft_strdup("");
	while (env && env->value)
	{
		get_param_name(environemnt_name, env->value);
		if (ft_strcmp(arg, environemnt_name) == 0)
		{
			ft_memdel(environemnt_val);
			environemnt_val = environment_value(env->value);
			return (environemnt_val);
		}
		env = env->next;
	}
	return (environemnt_val);
}
