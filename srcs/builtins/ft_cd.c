/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 21:48:04 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/08 19:43:58 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cwd_to_old(t_environement *env)
{
	char	cwd[BUFF_SIZE];
	char	*oldpwd;

	if (getcwd(cwd, BUFF_SIZE) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!(oldpwd))
		return (ERROR);
	if (already_there(env, oldpwd) == 0)
		increment_env(oldpwd, env);
	ft_memdel(oldpwd);
	return (SUCCESS);
}

static char	*extract(t_environement *env, const char *var, size_t len)
{
	char	*path;
	int		i;
	int		j;
	int		length;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			length = ft_strlen(env->value) - len;
			path = malloc(sizeof(char) * length + 1);
			if (!(path))
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++])
				if (i > (int)len)
					path[j++] = env->value[i];
			path[j] = '\0';
			return (path);
		}
		env = env->next;
	}
	return (NULL);
}

static void	throw_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putendl_fd("too many arguments ", 2);
	else
	{
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(":", 2);
		ft_putendl_fd("	No such file or directory", 2);
	}
}

static int	move_to(int flag, t_environement *env)
{
	int		retvalue;
	char	*destination;

	destination = NULL;
	if (flag == 0)
	{
		cwd_to_old(env);
		destination = extract(env, "HOME", 4);
		if (!destination)
			return (ft_putendl_fd("Shell :cd: HOME not set", STDERR), ERROR);
	}
	else if (flag == 1)
	{
		destination = extract(env, "OLDPWD", 6);
		if (!destination)
		{
			ft_putendl_fd("minishell : cd: HOME not set", STDERR);
			return (ERROR);
		}
		cwd_to_old(env);
	}
	retvalue = chdir(destination);
	ft_memdel(destination);
	return (retvalue);
}

int	ft_cd(char **args, t_environement *env)
{
	int		retvalue;

	if (!args[1])
		return (move_to(0, env));
	if (ft_strcmp(args[1], "-") == 0)
		retvalue = move_to(1, env);
	else
	{
		cwd_to_old(env);
		retvalue = chdir(args[1]);
		if (retvalue < 0)
			retvalue *= -1;
		if (retvalue != 0)
			throw_error(args);
	}
	return (retvalue);
}
