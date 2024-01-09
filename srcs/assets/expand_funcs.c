/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:31:18 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/08 23:52:49 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*obtain(const char *arg, int pos, t_environement *env, int ret)
{
	char	buffer[BUFF_SIZE];
	char	*value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		value = ft_itoa(ret);
		return (value);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && legal_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		buffer[i] = arg[pos];
		pos++;
		i++;
	}
	buffer[i] = '\0';
	value = obtain_value(buffer, env);
	return (value);
}

int	return_length(int ret_value)
{
	char	*dummy;
	int		ret_len;

	dummy = ft_itoa(ret_value);
	ret_len = ft_strlen(dummy);
	ft_memdel(dummy);
	return (ret_len);
}

int	obtain_len(const char *arg, int pos, t_environement *env, int ret)
{
	char	name[BUFF_SIZE];
	char	*value;
	int		length;

	length = 0;
	if (arg[pos] == '?')
		return (return_length(ret));
	if (ft_isdigit(arg[pos]))
		return (0);
	while (arg[pos] && legal_char(arg[pos]) == 1 && length < BUFF_SIZE)
	{
		name[length] = arg[pos];
		pos++;
		length++;
	}
	name[length] = '\0';
	value = obtain_value(name, env);
	length = ft_strlen(value);
	ft_memdel(value);
	return (length);
}

int	alloc_length(const char *arg, t_environement *env, int ret)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == EXPANSION)
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += obtain_len(arg, i, env, ret);
		}
		size++;
	}
	return (size);
}
