/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expander_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:25:45 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/17 16:23:38 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*ft_expand_util_herdoc(char *s, t_env_copy *env)
{
	char	*var_name;
	int		i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '$') 
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
		{
			var_name = get_var(s + (i + 1));
			s = ft_expand_result(s, i, var_name, env);
			free(var_name);
		}
		if (s[i])
			i++;
	}
	return (s);
}

char	*ft_expand_herdoc(char *s, t_env_copy *env)
{
	if (!s)
		return (NULL);
	s = ft_expand_util_herdoc(ft_strdup(s), env);
	return (s);
}
