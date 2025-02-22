#include "header.h"

void	push(t_stack **stack1, t_stack **stack2)
{
	t_stack	*tmp;

	if (!stack1 || !(*stack1))
		return ;
	tmp = *stack1;
	*stack1 = (*stack1)->next;
	tmp->next = NULL;
	ft_lstadd_front(stack2, tmp);
}