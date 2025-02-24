#include "header.h"

void	pa(t_stack **stack1, t_stack **stack2) // stack_b stack_a
{
	t_stack	*tmp;

	if (!stack1 || !(*stack1))
		return ;
	tmp = *stack1;
	*stack1 = (*stack1)->next;
	tmp->next = NULL;
	ft_lstadd_front(stack2, tmp);
	write(1, "pa\n", 3);
}

void	pb(t_stack **stack1, t_stack **stack2) //stack_a stack_b
{
	t_stack	*tmp;

	if (!stack1 || !(*stack1))
		return ;
	tmp = *stack1;
	*stack1 = (*stack1)->next;
	tmp->next = NULL;
	ft_lstadd_front(stack2, tmp);
	write(1, "pb\n", 3);
}
