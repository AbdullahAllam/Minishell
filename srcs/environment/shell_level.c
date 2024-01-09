/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:01:34 by ama10362          #+#    #+#             */
/*   Updated: 2023/12/30 17:02:44 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_neglect_space(const char *str, int *i)
{
	while ((str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n')
		|| (str[*i] == '\r' || str[*i] == '\v' || str[*i] == '\f'))
		(*i)++;
}

static int	check_invalid(const char *shlvl)
{
	int		i;

	i = 0;
	while (shlvl[i])
	{
		if (!(shlvl[i] >= '0' && shlvl[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	extract_level(const char *shlvl)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	ft_neglect_space(shlvl, &i);
	if (check_invalid(shlvl))
		return (0);
	if (shlvl[i] == '-')
		sign = -1;
	if (shlvl[i] == '-' || shlvl[i] == '+')
		i++;
	while (shlvl[i] >= '0' && shlvl[i] <= '9')
		num = num * 10 + (shlvl[i++] - '0');
	return (num * sign);
}

char	*get_param_name(char *param_name, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		param_name[i] = src[i];
		i++;
	}
	param_name[i] = '\0';
	return (param_name);
}

void	increase_shlvl(t_environement *env)
{
	int		shlvl;
	char	param_name[BUFF_SIZE];
	char	*shlvl_sub;
	char	*shlvl_string;

	shlvl_string = obtain_value("SHLVL", env);
	if (ft_strcmp(shlvl_string, "") == 0)
		return ;
	shlvl = extract_level(shlvl_string) + 1;
	ft_memdel(shlvl_string);
	while (env && env->next)
	{
		get_param_name(param_name, env->value);
		if (ft_strcmp("SHLVL", param_name) == 0)
		{
			ft_memdel(env->value);
			shlvl_sub = ft_itoa(shlvl);
			env->value = ft_strjoin("SHLVL=", shlvl_sub);
			ft_memdel(shlvl_sub);
			return ;
		}
		env = env->next;
	}
}
