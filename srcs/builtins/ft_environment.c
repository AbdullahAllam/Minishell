/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:48:43 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/01 13:49:04 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_environement *environment)
{
	while (environment)
	{
		ft_putendl(environment->value);
		environment = environment->next;
	}
	return (SUCCESS);
}
