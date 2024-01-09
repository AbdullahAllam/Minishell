/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:47:59 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/08 18:47:22 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	increment_env(const char *value, t_environement *env)
{
	t_environement	*to_add;
	t_environement	*dummy;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	to_add = malloc(sizeof(t_environement));
	if (!(to_add))
		return (-1);
	to_add->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	dummy = env->next;
	env->next = to_add;
	to_add->next = dummy;
	return (SUCCESS);
}

static int	throw_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	already_there(t_environement *env, char *args)
{
	char	buffer1[BUFF_SIZE];
	char	buffer2[BUFF_SIZE];

	get_param_name(buffer1, args);
	while (env && env->next)
	{
		get_param_name(buffer2, env->value);
		if (ft_strcmp(buffer1, buffer2) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	ft_export(char **a, t_environement *env, t_environement *add)
{
	int		existing_flag;
	int		error_flag;

	existing_flag = 0;
	if (!a[1])
		no_arg_response(add);
	else
	{
		error_flag = legal_env(a[1]);
		if (a[1][0] == '=')
			error_flag = -3;
		if (error_flag <= 0)
			return (throw_error(error_flag, a[1]));
		if (error_flag == 2)
			existing_flag = 1;
		else
			existing_flag = already_there(env, a[1]);
		if (existing_flag == 0)
		{
			if (error_flag == 1)
				increment_env(a[1], env);
			increment_env(a[1], add);
		}
	}
	return (SUCCESS);
}
