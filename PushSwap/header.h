/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:37:28 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/02/06 21:49:31 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_stacka
{
	int				data;
	struct s_stacka	*next;
}t_stack;

char			**ft_split(char const *s, char c);
void			ft_lstclear(t_stack **stack_a);
void			ft_lstadd_back(t_stack **stack_a, t_stack *new);
long long		ft_atoi(const char *str);
t_stack			*ft_lstnew(int data);
void			swap(t_stack **stack_a);
void			swap_both(t_stack **stack_a, t_stack **stack_b);
void			push(t_stack **stack1, t_stack **stack2);
void			rotate(t_stack **stack);
void			ft_lstadd_front(t_stack **lst, t_stack *new);
void			rrotate(t_stack **stack);
void			rrotate_both(t_stack **stacka, t_stack **stackb);
void			rotate_both(t_stack **stacka, t_stack **stackb);
#endif