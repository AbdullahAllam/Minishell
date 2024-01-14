/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:58:56 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/01 13:59:07 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	current_wd[BUFF_SIZE];

	if (getcwd(current_wd, BUFF_SIZE))
	{
		ft_putendl_fd(current_wd, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
