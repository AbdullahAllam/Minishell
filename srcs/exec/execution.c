/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:29:20 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/09 01:30:12 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**commands_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		return (NULL);
	token = start;
	i = 0;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	master_exec(t_minishell *minishell, t_token *token)
{
	char			**tab;
	int				i;
	t_environement	dummy;

	dummy = *(minishell->environment);
	if (minishell->childroute == 0)
		return ;
	tab = commands_tab(token);
	i = 0;
	while (tab && tab[i])
	{
		tab[i] = expand(tab[i], minishell->environment, minishell->retvalue);
		i++;
	}
	if (tab && ft_strcmp(tab[0], "exit") == 0 && includes_pipe(token) == 0)
		ft_exit(minishell, tab);
	else if (tab && check_builtin(tab[0]))
		minishell->retvalue = do_built_in(tab, minishell);
	else if (tab)
		minishell->retvalue = bin_exc(tab, &dummy, minishell);
	clean_tab(tab);
	close_2_fds(minishell->pipin, minishell->pipout);
	minishell->pipin = -1;
	minishell->pipout = -1;
	minishell->childroute = 0;
}
