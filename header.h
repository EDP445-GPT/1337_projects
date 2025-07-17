/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:56:54 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/17 20:51:58 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "includes/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <ctype.h>

# define MAX_PATH 1024

typedef enum s_TokenType{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND_OUT,
	TOKEN_HEREDOC,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_ENV_VAR,
	TOKEN_EXIT_STATUS,
	TOKEN_EOF,
	TOKEN_ERROR
}	t_TokenType;

typedef struct s_tokens
{
	t_TokenType		type;
	char			*value;
	struct s_tokens	*next;
}	t_tokens;

typedef enum s_type_redic
{
	HEREDOC,
	APPEND,
	IN,
	OUT
}	t_type_redic;

typedef struct s_redic
{
	t_type_redic	type;
	char			*file;
	int				fd_heredoc;
}	t_redic;

typedef struct s_command
{
	char			**args;
	t_redic			**redirctions;
}	t_command;

typedef struct s_env_copy
{
	char				*name;
	char				*value;
	struct s_env_copy	*next;
}	t_env_copy;

typedef struct s_exec
{
	pid_t	pid;
	int		pids;
	int		status;
	char	*path;
	int		pipe_fd[2];
	int		i;
	char	**envp;
}	t_exec;

typedef struct s_parse
{
	int			j;
	int			k;
	int			i;
	t_env_copy	*env;
	int			arguments_flag;
}	t_parse;

char		**lexer_custom_split(char const *s);
char		**custom_split(char const *s);
t_tokens	*new_node(int type, char *value);
void		add_to_list(t_tokens **tokens, int type, char *value);
int			is_pipe(char *str);
int			is_redirect_in(char *str);
int			is_redirect_out(char *str);
int			is_heredoc(char *str);
int			is_append_out(char *str);
t_tokens	*tokenizer(char *str);
t_env_copy	*lstnew(char *name, char *value);
void		lstadd_back(t_env_copy **lst, t_env_copy *new);
char		*ft_strdup_name(char *src);
char		*ft_strdup_value(char *src);
int			lexer(char *str, t_env_copy *envp);
void		free_tokens(char **strs);
void		ft_parser(t_tokens *tokens, t_env_copy *p);
int			lstsize(t_list *lst);
char		*ft_get_env_value(char *name, t_env_copy *p);
char		*ft_expand( char *s, t_env_copy *p);
char		**ft_split_args(char *str, t_env_copy *env);
char		**struct_to_arr_env(t_env_copy *env);
void		exec_command(t_command **cmd, t_env_copy *env);
void		ft_pwd(t_env_copy *env);
char		*find_path(t_env_copy *envp);
void		ft_export(t_command **cmd, t_env_copy *env);
void		ft_cd(t_command **cmd, t_env_copy *env); 
void		update_environment(t_env_copy *env, char *key, char *new_value);
void		lst_delete_node(t_env_copy **lst, t_env_copy *node);
void		ft_echo(char **argument);
void		ft_env(t_env_copy *env);
void		ft_exit(char **arguments, t_env_copy *env);
void		ft_unset(t_env_copy *env, char **var);
t_env_copy	*find_key(t_env_copy *env, char *key);
void		*heredoc(t_command **cmd, t_env_copy *env);
void		handle_redirection(t_command *cmd, t_env_copy *env);
char		*ft_substr_expand(char const *s, unsigned int start, size_t len);
char		**ft_split_args_file(char *str);
char		*skip_qoute(char *str);
char		*check_valid_path(char *path, char *cmd);
void		add_to_list_pwd(t_env_copy *env, char *name, char *value);
t_env_copy	*new_node_pwd(char *name, char *value);
int			check_herdoc(t_tokens *tokens);
char		*ft_expand_herdoc(char *s, t_env_copy *env);
int			is_redirection_token(char *token);
int			is_pipe_token(char *token);
int			is_special_token(char *token);
int			is_only_space(char *token);
int			check_quotes(char *str);
char		**ft_split_args_file_qoute(char *str);
void		print_invalid_export_option(char *name, t_env_copy *env);
void		print_export(t_env_copy *env);
int			ft_isalnum_env(char *s);
void		print_invalid_export_id(char *name, t_env_copy *env);
void		export_args(t_env_copy *env, char *value, int j, char *args);
void		print_cd_err(t_env_copy *env);
int			check_dir(char *str, t_env_copy *env);
int			get_update_cwd(t_env_copy *env, char *target, char *old_cwd);
char		*get_home_direc(t_env_copy *env);
int			update_env_pwd(char *new_cwd, t_env_copy *env);
int			update_env_oldpwd(char *old_cwd, t_env_copy *env);
char		*ft_expand_util(char *s, t_env_copy *env, int single_flag,
				int double_flag);
char		**split_args_filler(char **args, char *str, int single_qoute,
				int double_qoute);
char		**ft_alocate_args(char *str);
char		**split_args_filler_qoute(char **args, char *str, int single_qoute,
				int double_qoute);
void		handle_param_after_file(t_command **cmd, t_parse *pr,
				char **arguments);
void		handle_redirs_file(t_command **cmd, t_parse *pr, char *s);
void		handle_param_after_herdoc(t_command **cmd, t_parse *pr,
				char **arguments);
void		handle_herdoc_delimiter(t_command **cmd, t_parse *pr, char *s);
int			c_count(t_tokens *tokens);
t_command	**c_alocate(t_tokens *p);
int			count_args(t_tokens *tmp);
int			c_redic(t_tokens *tmp);
t_tokens	*handle_pipe_token(t_command **cmd, t_parse *pr,
				t_tokens *tokens);
t_tokens	*process_command_tokens(t_command **cmd, t_parse *pr,
				t_tokens *tokens);
void		init_parser(t_parse *pr, t_env_copy *p);
void		finalize_last_command(t_command **cmd, t_parse *pr);
void		handle_word_token(t_command **cmd, t_parse *pr, t_tokens *tokens);
t_tokens	*handle_input_redirect(t_command **cmd, t_parse *pr,
				t_tokens *tokens);
t_tokens	*handle_output_redirect(t_command **cmd, t_parse *pr,
				t_tokens *tokens);
t_tokens	*handle_heredoc_token(t_command **cmd, t_parse *pr,
				t_tokens *tokens);
t_tokens	*handle_append_redirect(t_command **cmd, t_parse *pr,
				t_tokens *tokens);
void		signal_handler();
char		*ft_expand_util_herdoc(char *s, t_env_copy *env);
char		*ft_expand_herdoc(char *s, t_env_copy *env);
char		*ft_get_env_value(char *name, t_env_copy *env);
char		*get_var(char *s);
char		*ft_expand_result(char *s, int i, char *var_name, t_env_copy *env);
void		cmd_not_found(t_env_copy *env, t_command **cmd, int i);
#endif