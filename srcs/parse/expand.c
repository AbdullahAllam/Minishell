/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:27:39 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/08 23:42:00 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_var(char *dest, const char *src, int pos)
{
	int		i;

	i = 0;
	while (src[i])
		dest[pos++] = src[i++];
	return (i);
}

static void	put_var(t_expand *ex, char *arg, t_environement *env, int ret)
{
	char	*env_value;

	env_value = obtain(arg, ex->j, env, ret);
	if (env_value)
		ex->i += copy_var(ex->replace, env_value, ex->i);
	ft_memdel(env_value);
	if (arg[ex->j] == '?')
		ex->j++;
	while (legal_char(arg[ex->j]) == 1)
		ex->j++;
}

char	*expand(char *arg, t_environement *env, int retvalue)
{
	t_expand	ex;
	int			length;

	length = alloc_length(arg, env, retvalue);
	ex.replace = malloc(sizeof(char) * length + 1);
	if (!(ex.replace))
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < length && arg[ex.j])
	{
		if (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')
				ex.replace[ex.i++] = '$';
			else
				put_var(&ex, arg, env, retvalue);
		}
		ex.replace[ex.i++] = arg[ex.j++];
	}
	ex.replace[ex.i] = '\0';
	return (ex.replace);
}
