/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_response.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:33:12 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/08 18:40:57 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_in_order(char **vars_list, int count)
{
	int		sort_flag;
	int		i;
	char	*dummy;

	sort_flag = 0;
	while (vars_list && sort_flag == 0)
	{
		sort_flag = 1;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(vars_list[i], vars_list[i + 1]) > 0)
			{
				dummy = vars_list[i];
				vars_list[i] = vars_list[i + 1];
				vars_list[i + 1] = dummy;
				sort_flag = 0;
			}
			i++;
		}
		count--;
	}
}

int	var_counter(char **vars)
{
	int		i;

	i = 0;
	while (vars[i])
		i++;
	return (i);
}

void	no_arg_response(t_environement *environement)
{
	int		i;
	char	**vars_list;
	char	*vars_str;

	vars_str = into_str(environement);
	vars_list = ft_split(vars_str, '\n');
	ft_memdel(vars_str);
	put_in_order(vars_list, var_counter(vars_list));
	i = 0;
	while (vars_list[i])
	{
		ft_putstr("declare -x ");
		ft_putendl(vars_list[i]);
		i++;
	}
	clean_tab(vars_list);
}
