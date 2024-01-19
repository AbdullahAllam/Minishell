/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:13:58 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/19 23:59:19 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_i_j(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

static char	*sep_space_alloc(char *line_cmd)
{
	char	*mod_length;
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	while (line_cmd[i])
	{
		if (is_separating(line_cmd, i))
			counter++;
		i++;
	}
	mod_length = malloc(sizeof(char) * (i + 2 * counter + 1));
	if (!(mod_length))
		return (NULL);
	return (mod_length);
}

static char	*sep_to_space(char *line)
{
	char	*mod_line;
	int		i;
	int		j;

	initialize_i_j(&i, &j);
	mod_line = sep_space_alloc(line);
	while (mod_line && line[i])
	{
		if (check_q(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			mod_line[j++] = (char)(-line[i++]);
		else if (check_q(line, i) == 0 && is_separating(line, i))
		{
			mod_line[j++] = ' ';
			mod_line[j++] = line[i++];
			if (check_q(line, i) == 0
				&& ((line[i] == '>' && line[i - 1] == '>')
					|| (line[i] == '<' && line[i - 1] == '<')))
				mod_line[j++] = line[i++];
			mod_line[j++] = ' ';
		}
		else
			mod_line[j++] = line[i++];
	}
	mod_line[j] = '\0';
	return (ft_memdel(line), mod_line);
}

static int	open_quote_check(t_minishell *minishell, char **line_cmd)
{
	if (check_q(*line_cmd, LINE_LENGTH))
	{
		ft_putendl_fd("CATSHELL: OPEN QUOTES ERROR", STDERR);
		ft_memdel(*line_cmd);
		minishell->retvalue = 2;
		minishell->first_token = NULL;
		return (1);
	}
	return (0);
}

void	parse_line(t_minishell *minishell)
{
	char			*line_cmd;

	signals_handle();
	if (minishell->retvalue)
		ft_putstr_fd("😿 ", STDERR);
	else
		ft_putstr_fd("😻 ", STDERR);
	line_cmd = readline("\001\033[0;36m\033[1m\002CATSHELL ▸\001\033[0m\002");
	if (line_cmd == NULL)
	{
		minishell->exitflag = 1;
		ft_memdel(line_cmd);
		ft_putendl_fd("exit 😽", STDERR);
		return ;
	}
	if (line_cmd && *line_cmd)
		add_history(line_cmd);
	if (open_quote_check(minishell, &line_cmd))
		return ;
	line_cmd = sep_to_space(line_cmd);
	if (line_cmd && line_cmd[0] == '$')
		line_cmd[0] = (char)(-line_cmd[0]);
	minishell->first_token = obtain_tokens(line_cmd);
	ft_memdel(line_cmd);
	arrange_args(minishell);
}
