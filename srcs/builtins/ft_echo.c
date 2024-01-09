/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:38:20 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/01 18:47:02 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	arg_number(char **options)
{
	int		num;

	num = 0;
	while (options[num])
		num++;
	return (num);
}

int	ft_echo(char **options)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (arg_number(options) > 1)
	{
		while (options[i] && ft_strcmp(options[i], "-n") == 0)
		{
			n_flag = 1;
			i++;
		}
		while (options[i])
		{
			ft_putstr_fd(options[i], 1);
			if (options[i + 1] && options[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_flag == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
