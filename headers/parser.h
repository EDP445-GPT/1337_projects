#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include "../tokenizer_one/tokenizer_one.h"
#include <stdio.h>
#include <fcntl.h>
#include "../includes/libft/libft.h"
#include "../header.h"
#include "../expander/expander.h"
#include "../execution/execution.h"

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
	char			*delimiter;
} t_redic;

typedef struct s_command
{
	char			**args;
	t_redic			**redirctions;
	int				pipe_counter;
} t_command ;

void	ft_parser(t_tokens *tokens, t_env_copy *p);
// char		*expand(const char *s, t_env_copy *p);

#endif