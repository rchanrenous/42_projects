/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:16:09 by rchan--r          #+#    #+#             */
/*   Updated: 2023/04/22 23:31:19 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>

# define WRITE 1
# define READ 0

# define HEREDOC_EOF "minishell: warning: here-document \
	delimited by end-of-file (wanted `%s')\n"

# define SIZE_BUF_GETCWD 1024

typedef enum e_cwd_type
{
	VAR,
	NO_VAR
}	t_cwd_type;

typedef enum e_str_protect
{
	HEREDOC,
	PARSING
}	t_str_protect;

typedef enum e_stype
{
	DQ,
	NQ,
	ALL,
	NO
}	t_stype;

typedef enum e_redir
{
	IN1,
	IN2,
	OUT1,
	OUT2,
	INVALID,
	INVALID_PRINT
}	t_redir_type;

typedef enum e_close_fd
{
	CR,
	CW,
	NR,
	NW
}	t_close_fd;

typedef enum e_exec_type
{
	PIPE,
	NO_PIPE
}	t_exec_type;

typedef enum e_exec_mode
{
	HEREDOC_READ,
	PROMPT,
	EXEC
}	t_exec_mode;

typedef struct redir
{
	t_redir_type	type;
	char			*arg;
}	t_redir;

typedef struct cmd
{
	char	**cmd;
	t_list	*list_redir;
	int		fds[2];
}	t_cmd;

/* PARSING */
t_list	*parse(char *line, t_list *env);
char	*str_expand_nq(char *str, t_list *env);
t_list	*line_to_cmds(char *line);
t_list	*parse_cmd(char *str, t_list **list_redir);
int		str_resolve_quotes(char **str, t_list *env);
int		cmd_resolve_quotes(t_cmd *cmd, t_list *env);

int		index_end_token(char *line);

int		is_redir(char c);
int		is_redir_pipe_exp(char *str, t_stype type);
int		is_quote(char c);
int		is_arg_delim(char c);
int		index_end_quote(char *str);
int		closed_quotes(char *str);
int		lst_add_strldup(t_list **lst, char *line, int i);
char	*token_expand(char **str, t_list *env);
int		is_expandable(char *str, t_stype e);
char	*str_get_token(char *str, t_list *env);
char	*token_single_quote(char *str, t_list *env);
char	*token_double_quote(char *str, t_list *env);
char	*token_no_quote(char *str, t_list *env);
char	*str_protect(char *exp, t_str_protect type);

t_cmd	*cmd_new(void);
void	cmd_free(t_cmd **cmd);
void	cmd_free_void(void *cmd);

t_redir	*redir_new(t_redir_type type);
void	redir_free(t_redir **redir);
void	redir_free_void(void *redir);
int		get_redir_type(char *str, t_redir_type *type);

void	cmd_print_void(void *cmd); // debug

void	redir_print_void(void *redir); // debug

/* ENV */
int		env_init(t_list **lst, char **envp);
void	env_print(t_list *env);
int		is_var(void *content, void *var);
int		valid_var_name(char *name);
int		var_in_env(char *var, char *env_var);
int		ft_getenv(char *var, t_list *env, char **res);

void	print_str(void *content);

void	cmd_print(t_cmd *cmd);

/* BUILT-INS */
int		env_unset(t_list **env, char **cmd, t_exec_type exec_type);
int		env_export(t_list **env, char **cmd, t_exec_type exec_type);
int		ft_env(t_list *env, int fd);
int		ft_cd(char **cmd, t_list **env, t_exec_type exec_type);
int		ft_pwd(int fd);
int		ft_exit(char **cmd, t_exec_type exec_type);
int		ft_echo(t_cmd *cmd);

int		get_cwd_val(char **cwd, t_list *env, t_cwd_type type);

/* SIGNAL */
void	sig_setup(t_exec_mode mode);

/* EXEC */
int		get_line(char **line, t_list *env);
int		line_exec(t_list **env);

int		redir_check(t_list *list_cmd);
int		line_check_empty_cmd(t_list *list_cmd);
int		pipe_update_fds(t_list *list_cmd);
int		redir_update_fds(t_cmd *cmd, t_list *env);
int		redir_in2_update_fds(t_cmd *cmd, t_redir *redir, t_list *env);

int		cmd_close_fds(t_cmd *cmd, t_close_fd close_fd);
int		list_cmd_close_fds(t_list *list_cmd, t_close_fd close_fd);

int		cmd_system(t_list *list_cmd, t_list *env, int *nb_process);

int		is_dir_message(char *str);
int		check_dir_message(char *str);
int		cd_no_arg(char **arg, t_list *env);

int		get_exit_status(void);
void	set_exit_status(int val);
#endif
