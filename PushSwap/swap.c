#include "header.h"

void	swap(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack || !(*stack) || !((*stack)->next))
		return ;
	tmp = ft_lstnew((*stack)->data);
	(*stack)->data = ((*stack)->next)->data;
	((*stack)->next)->data = tmp->data;
	ft_lstclear(&tmp);
}

void	swap_both(t_stack **stack_a, t_stack **stack_b)
{
	swap(stack_a);
	swap(stack_b);
}