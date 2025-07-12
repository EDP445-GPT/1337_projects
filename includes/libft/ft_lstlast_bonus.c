/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:43:58 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/11/08 15:24:01 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;
	t_list	*another_ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr != NULL)
	{
		another_ptr = ptr;
		ptr = ptr->next;
	}
	return (another_ptr);
}
