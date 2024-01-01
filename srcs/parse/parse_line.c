/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:13:58 by ama10362          #+#    #+#             */
/*   Updated: 2023/12/30 17:37:27 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int code)
{
	(void)code;
	ft_putstr_fd("\b\b  ", STDERR);
	ft_putstr_fd("\n", STDERR);
	ft_putstr_fd("\033[0;36m\033[1m😿 minishell ▸ \033[0m", STDERR);
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

	i = 0;
	j = 0;
	mod_line = sep_space_alloc(line);
	while (mod_line && line[i])
	{
		if (check_q(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			mod_line[j++] = (char)(-line[i++]);
		else if (check_q(line, i) == 0 && is_separating(line, i))
		{
			mod_line[j++] = ' ';
			mod_line[j++] = line[i++];
			if (check_q(line, i) == 0 && line[i] == '>')
				mod_line[j++] = line[i++];
			mod_line[j++] = ' ';
		}
		else
			mod_line[j++] = line[i++];
	}
	mod_line[j] = '\0';
	ft_memdel(line);
	return (mod_line);
}

static int	open_quote_check(t_minishell *minishell, char **line_cmd)
{
	if (check_q(*line_cmd, LINE_LENGTH))
	{
		ft_putendl_fd("minishell: OPEN QUOTES ERROR", STDERR);
		ft_memdel(*line_cmd);
		minishell->retvalue = 2;
		minishell->first_token = NULL;
		return (1);
	}
	return (0);
}

void	parse_line(t_minishell *minishell)
{
	char	*line_cmd;

	signal(SIGINT, &sig_int);
	if (minishell->retvalue)
		ft_putstr_fd("😿 ", STDERR);
	else
		ft_putstr_fd("😻 ", STDERR);
	line_cmd = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
	if (line_cmd == NULL)
	{
		minishell->exitflag = 1;
		ft_putendl_fd("exit 😽", STDERR);
		return ;
	}
	if (line_cmd && *line_cmd)
		add_history(line_cmd);
	if (open_quote_check(minishell, &line_cmd))
		return ;
	line_cmd = sep_to_space(line_cmd);
	minishell->first_token = obtain_tokens(line_cmd);
	free(line_cmd);
	arrange_args(minishell);
}
