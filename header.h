#ifndef HEADER_H
#define HEADER_H



#include "includes/libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_PATH 1024
typedef enum {
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
} TokenType;

typedef struct s_tokens
{
	TokenType		type;
	char			*value;
	struct s_tokens	*next;
}	t_tokens;

typedef enum 
{
	HEREDOC,
	APPEND,
	IN,
	OUT
}   t_type_redic;

typedef struct s_redic
{
	t_type_redic	type;
	char			*file;
	int				fd_heredoc;
} t_redic;

typedef struct s_command
{
	char			**args;
	t_redic			**redirctions;
} t_command ;

typedef struct s_env_copy
{
	char			*name;
	char			*value;
	struct s_env_copy	*next;
}t_env_copy;

char		**lexer_custom_split(char const *s);
char		**custom_split(char const *s);
//int		new_node(t_tokens **tokens, int type, char *value);
t_tokens	*new_node(int type, char *value);
void		add_to_list(t_tokens **tokens, int type, char *value);
int			is_pipe(char *str);
int			is_redirect_in(char *str);
int			is_redirect_out(char *str);
int			is_heredoc(char *str);
int			is_append_out(char *str);
int			is_single_q(char *str);
t_tokens	*tokenizer(char *str);
// int			lstsize(t_env_copy *lst);
t_env_copy	*lstnew(char *name, char *value);
// void		lstdelone(t_env_copy *lst);
// void		lstclear(t_env_copy **lst);
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
void 		ft_env(t_env_copy *env);
void 		ft_exit(char **arguments, t_env_copy *env);
void 		ft_unset(t_env_copy *env, char **var);
t_env_copy	*find_key(t_env_copy *env, char *key);
void		*heredoc(t_command **cmd, t_env_copy *env);
void		signal_handler();
void    	handle_redirection(t_command *cmd);
char		*ft_substr_expand(char const *s, unsigned int start, size_t len);
char		**ft_split_args_file(char *str);
char		*skip_qoute(char *str);
char		*check_valid_path(char *path, char *cmd);
#endif