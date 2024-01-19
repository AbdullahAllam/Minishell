/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:29:12 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/20 02:15:05 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join(const char *link, const char *binary)
{
	char	*dummy;
	char	*path;

	dummy = ft_strjoin(link, "/");
	path = ft_strjoin(dummy, binary);
	ft_memdel(dummy);
	return (path);
}

char	*search_dir(char *link, char *cmd)
{
	DIR				*folder;
	struct dirent	*binary;
	char			*path;

	path = NULL;
	folder = opendir(link);
	if (!folder)
		return (NULL);
	binary = readdir(folder);
	while (binary)
	{
		if (ft_strcmp(binary->d_name, cmd) == 0)
			path = join(link, binary->d_name);
		binary = readdir(folder);
	}
	closedir(folder);
	return (path);
}

int	throw_error(char *cmd)
{
	DIR	*folder;
	int	fd;
	int	ret;

	folder = opendir(cmd);
	fd = open(cmd, O_WRONLY);
	ft_putstr_fd("CATSHELL: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	print_error(cmd, fd, folder);
	if (ft_strchr(cmd, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	close_fd(fd);
	return (ret);
}

int	execute(char *link, char **args, t_environement *env, t_minishell *mini)
{
	int		ret;	
	char	**environment;
	char	*str;
	pid_t	pid;

	ret = SUCCESS;
	pid = fork();
	if (pid == 0)
	{
		str = into_str(env);
		environment = ft_split(str, '\n');
		ft_memdel(str);
		if (ft_strchr(link, '/') != NULL)
			execve(link, args, environment);
		ret = throw_error(link);
		clean_tab(environment);
		clean_token(mini->first_token);
		rl_clear_history();
		clean_all_env(mini);
		exit(ret);
	}
	else
		waitpid(pid, &ret, 0);
	ret = extra_lines_3(ret);
	return (ret);
}

int	bin_exc(char **args, t_environement *dummy, t_minishell *mini)
{
	int				i;
	char			**links;
	char			*path;
	int				ret;

	g_sigf = 2;
	i = 0;
	ret = UNKNOWN_COMMAND;
	while (dummy && dummy->value && ft_strncmp(dummy->value, "PATH=", 5) != 0)
		dummy = dummy->next;
	if (dummy == NULL || dummy->next == NULL)
		return (execute(args[0], args, dummy, mini));
	links = ft_split(dummy->value, ':');
	if (!args[0] && !links[0])
		return (ERROR);
	i = 1;
	path = search_dir(links[0] + 5, args[0]);
	while (args[0] && links[i] && path == NULL)
		path = search_dir(links[i++], args[0]);
	if (path != NULL)
		ret = execute(path, args, mini->environment, mini);
	else
		ret = execute(args[0], args, mini->environment, mini);
	post_binary(links, path);
	return (ret);
}
