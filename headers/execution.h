
#ifndef EXECUTION_H
#define EXECUTION_H

#include <stdlib.h>
#include "../includes/libft/libft.h"
#include "../header.h"
#include "../tokenizer_one/tokenizer_one.h"
#include "../parser/parser.h"

char	**struct_to_arr_env(t_env_copy *env);
void    exec_command(t_command *cmd, t_env_copy *env);
#endif