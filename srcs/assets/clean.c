/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:03:24 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/20 02:16:06 by ama10362         ###   ########.fr       */
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

void	clean_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_memdel(tab[i]);
		i++;
	}
	if (tab)
		ft_memdel(tab);
}

void	clean_all_env(t_minishell *mini)
{
	clean_environment(mini->additional_environment);
	clean_environment(mini->environment);
}

void	post_binary(char **links, char *path)
{
	clean_tab(links);
	ft_memdel(path);
	g_sigf = 0;
}
