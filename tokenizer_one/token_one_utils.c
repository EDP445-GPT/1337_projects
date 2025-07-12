
#include "../header.h"

int is_pipe(char *str)
{
    if (str[0] == '|' && !str[1])
        return (1);
    else
        return (0);
}

int is_redirect_in(char *str)
{
    if (str[0] == '<' && !str[1])
        return (1);
    else
        return (0);
}

int is_redirect_out(char *str)
{
    if (str[0] == '>' && !str[1])
        return (1);
    else
        return (0);
}

int is_heredoc(char *str)
{
    if (str[0] == '<' && str[1] == '<' && !str[2])
        return (1);
    else
        return (0);
}

int is_append_out(char *str)
{
    if (str[0] == '>' && str[1] == '>' && !str[2])
        return (1);
    else
        return (0);
}