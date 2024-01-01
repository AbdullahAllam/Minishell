/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:39:36 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/01 18:41:09 by ama10362         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define LINE_LENGTH 2147483647 // max allowed line length
# define EXPANSION -36 //for $ sign
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_environment
{
	char					*value;
	struct s_environment	*next;
}				t_environement;

typedef struct s_minishell
{
	t_token			*first_token;
	t_environement	*environment;
	t_environement	*additional_environment;
	int				input;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				retvalue;
	int				exitflag;
	int				not_executed;
}				t_minishell;

// typedef struct	s_expansions
// {
// 	char			*new_arg;
// 	int				i;
// 	int				j;
// }				t_expansions;

/*
** MINISHELL
*/
// void			redir(t_mini *mini, t_token *token, int type);
// void			input(t_mini *mini, t_token *token);
// int				minipipe(t_mini *mini);
// char			*expansions(char *arg, t_env *env, int ret);

/*
** EXEC
*/
// void			exec_cmd(t_mini *mini, t_token *token);
// int				exec_bin(char **args, t_env *env, t_mini *mini);
// int				exec_builtin(char **args, t_mini *mini);
// int				is_builtin(char	*command);

/*
** BUILTINS
*/
int				ft_env(t_environement *environment);
int				ft_pwd(void);
void			ft_exit(t_minishell *minishell, char **args);
int				ft_unset(char **arg, t_minishell *minishell);
int				ft_echo(char **options);
// int				ft_cd(char **args, t_env *env);
// int				ft_export(char **args, t_env *env, t_env *secret);
// int				env_add(const char *value, t_env *env);
// char			*get_env_name(char *dest, const char *src);
// int				is_in_env(t_env *env, char *args);

/*
** PARSE
*/
void			parse_line(t_minishell *minishell);
int				validate_line(t_minishell *minishell, t_token *token);
int				check_q(char *line_cmd, int length);
int				is_separating(char *line_cmd, int i);
t_token			*obtain_tokens(char *line_cmd);
int				neglect_sep(char *line_cmd, int i);
void			classify_type(t_token *token, int sep_neglect);
int				is_last_valid_arg(t_token *token);
void			arrange_args(t_minishell *minishell);

/*
** ENV
*/
int				initiate_env(t_minishell *minishell, char **env_array);
int				additional_env_init(t_minishell *minishell, char **env_array);
void			increase_shlvl(t_environement *env);
char			*get_param_name(char *param_name, const char *src);
char			*obtain_value(char *arg, t_environement *env);
char			*environment_value(char *env_value);
void			ft_neglect_space(const char *str, int *i);

// char			*env_to_str(t_env *lst);
// int				is_env_char(int c);
// int				is_valid_env(const char *env);
// void			print_sorted_env(t_env *env);
// size_t			size_env(t_env *lst);

/*
** ASSETS
*/
void			initiate_fds(t_minishell *minishell);
void			initiate_shell(t_minishell *minishell);
// void			reset_std(t_mini *mini);
// void			close_fds(t_mini *mini);
// void			ft_close(int fd);

void			clean_environment(t_environement *environment);
void			clean_token(t_token *first_token);
// void			free_tab(char **tab);

// t_token			*next_sep(t_token *token, int skip);
t_token			*prev_sep(t_token *token, int skip);
// t_token			*next_run(t_token *token, int skip);

int				of_kind(t_token *token, int type);
t_token			*find_next(t_token *token, int type, int skip);
int				of_kinds(t_token *token, char *types);
int				includes_type(t_token *token, int type);
int				includes_pipe(t_token *token);

void			extra_lines(int *i, char *c);
void			extra_lines_2(t_minishell *minishell);

/*
** EXPANSIONS
*/
// int				ret_size(int ret);
// int				get_var_len(const char *arg, int pos, t_env *env, int ret);
// int				arg_alloc_len(const char *arg, t_env *env, int ret);
// char			*get_var_value(const char *arg, int pos, t_env *env, int ret);

#endif
