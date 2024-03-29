/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ama10362 <ama10362@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:39:36 by ama10362          #+#    #+#             */
/*   Updated: 2024/01/20 02:25:26 by ama10362         ###   ########.fr       */
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
# include <sys/stat.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define DELIM 6
# define PIPE 7
# define END 8

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define BUFFER_SIZE 1
# define LINE_LENGTH 2147483647 // max allowed line length
# define EXPANSION -36 //for $ sign
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

extern int	g_sigf;

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

typedef struct s_expand
{
	char			*replace;
	int				i;
	int				j;
}				t_expand;

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
	int				childroute;
	int				parent;
	int				last;
	int				retvalue;
	int				exitflag;
	int				dont_exec;
}				t_minishell;

/*
** MINISHELL
*/
void			input_direct(t_minishell *mini, t_token *token);
void			out_direct(t_minishell *mini, t_token *token, int type);
int				pipe_direct(t_minishell *minishell, t_token *token);
void			brain(t_minishell *mini, t_token *token);
void			mixed_seps_case(t_minishell *mini, t_token *token);
void			child_job(t_minishell *minishell, int *pipefd);
void			heredoc_loop(t_minishell *mini, t_token *t);

/*
** EXEC
*/
int				check_builtin(char *cmd);
int				do_built_in(char **args, t_minishell *minishell);
int				bin_exc(char **args, t_environement *env, t_minishell *mini);
void			master_exec(t_minishell *minishell, t_token *token);

/*
** BUILTINS
*/
int				ft_env(t_environement *environment);
int				ft_pwd(void);
void			ft_exit(t_minishell *minishell, char **args);
int				ft_unset(char **arg, t_minishell *minishell);
int				ft_echo(char **options);
int				ft_cd(char **args, t_environement *env);
int				ft_export(char **a, t_environement *env, t_environement *add);
int				increment_env(const char *value, t_environement *env);
int				already_there(t_environement *env, char *args);

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
char			*expand(char *arg, t_environement *env, int retvalue);

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

char			*into_str(t_environement *list);
int				legal_char(int c);
int				legal_env(const char *env);
void			no_arg_response(t_environement *environement);

/*
** ASSETS
*/
void			initiate_fds(t_minishell *minishell);
void			initiate_shell(t_minishell *minishell);
void			close_fd(int fd);
void			close_2_fds(int fd1, int fd2);
void			close_fds(t_minishell *minishell);
void			reset_std(t_minishell *minishell);

void			clean_environment(t_environement *environment);
void			clean_all_env(t_minishell *mini);
void			clean_token(t_token *first_token);
void			clean_tab(char **tab);
void			post_binary(char **links, char *path);

t_token			*next_sep(t_token *token, int skip);
t_token			*prev_sep(t_token *token, int skip);
t_token			*next(t_token *token, int skip);
t_token			*previous(t_token *token, int skip);

int				of_kind(t_token *token, int type);
t_token			*find_next(t_token *token, int type, int skip);
int				of_kinds(t_token *token, char *types);
int				includes_type(t_token *token, int type);
int				includes_pipe(t_token *token);

void			extra_lines(int *i, char *c);
void			extra_lines_2(t_minishell *minishell);
int				extra_lines_3(int ret);
void			extra_lines_4(t_minishell *minishell, t_token *token);
int				extra_lines_5(t_minishell *minishell, int status);
void			print_error(char *cmd, int fd, DIR *folder);

/*
** EXPANSIONS
*/
char			*obtain(const char *arg, int pos, t_environement *env, int ret);
int				alloc_length(const char *arg, t_environement *env, int ret);

void			signals_handle(void);

/*
** GET_NEXT_LINE
*/
char			*get_next_line(int fd);
char			*ft_gnl_strjoin(char *s1, char *s2);

#endif
