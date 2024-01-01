/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:03:24 by ama10362          #+#    #+#             */
/*   Updated: 2023/12/30 17:08:34 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_environment(t_environement *environment)
{
	t_environement	*dummy;

	while (environment && environment->next)
	{
		dummy = environment;
		environment = environment->next;
		ft_memdel(dummy->value);
		ft_memdel(dummy);
	}
	ft_memdel(environment->value);
	ft_memdel(environment);
}

void	clean_token(t_token *first_token)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = first_token;
	while (current_token != NULL)
	{
		next_token = current_token->next;
		ft_memdel(current_token->str);
		ft_memdel(current_token);
		current_token = next_token;
	}
}
