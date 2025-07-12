#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

typedef struct s_env_copy
{
	char			*name;
	char			*value;
	struct s_env_copy	*next;
}t_env_copy;

// int			lstsize(t_env_copy *lst);
t_env_copy	*lstnew(char *name, char *value);
// void		lstdelone(t_env_copy *lst);
// void		lstclear(t_env_copy **lst);
void		lstadd_back(t_env_copy **lst, t_env_copy *new);
char		*ft_strdup_name(char *src);
char		*ft_strdup_value(char *src);

#endif